#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <time.h>
#include <math.h>
using namespace std;

#define BASE 26
#define MAX_COUNT 10000

// class node
// {
// public:
//     node()
//     {
//         flag = false;
//         for (int i = 0; i < BASE; i++)
//             next[i] = nullptr;
//     }
//     bool flag;
//     node *next[BASE];
// };

// class Trie
// {

// public:
//     Trie()
//     {
//         root = new node();
//     }
//     bool insert(string word)
//     {
//         node *p = root;
//         for (auto x : word)
//         {
//             int ind = x - 'a';
//             if (p->next[ind] == nullptr)
//                 p->next[ind] = new node();
//             p = p->next[ind];
//         }
//         if (p->flag)
//             return false;
//         p->flag = true;
//     }

//     bool search(string word)
//     {
//         node *p = root;
//         for (auto x : word)
//         {
//             int ind = x - 'a';
//             p = p->next[ind];
//             if (p == nullptr)
//                 return false;
//         }
//         return p->flag;
//     }
//     static void __output(node *root, string s)
//     {
//         if (root == nullptr)
//             return;
//         if (root->flag)
//             cout << "find : " << s << endl;
//         for (int i = 0; i < BASE; i++)
//         {
//             __output(root->next[i], s + char(i + 'a'));
//         }
//     }
//     void output()
//     {
//         __output(root, "");
//         return;
//     }
//     static void clearTrie(node *root)
//     {
//         if (root == nullptr)
//             return;
//         for (int i = 0; i < BASE; i++)
//             clearTrie(root->next[i]);
//         delete root;
//         return;
//     }
//     ~Trie()
//     {
//         clearTrie(root);
//     }

// private:
//     node *root;
// };

class node
{
public:
    int flag;
    int next[BASE];
    void clear()
    {
        flag = 0;
        for (int i = 0; i < BASE; i++)
        {
            next[i] = 0;
        }
    }
} trie[MAX_COUNT];

int cnt, root;
void clearTrie()
{
    cnt = 2, root = 1;
    trie[root].clear();
    return;
}
int getNewNode()
{
    trie[cnt].clear();
    return cnt++;
}
void insert(string s)
{
    int p = root;
    for (auto x : s)
    {
        int ind = x - 'a';
        if (trie[p].next[ind] == 0)
            trie[p].next[ind] = getNewNode();
        p = trie[p].next[ind];
    }
    trie[p].flag = 1;
    return;
}
bool search(string s)
{
    int p = root;
    for (auto x : s)
    {
        int ind = x - 'a';
        p = trie[p].next[ind];
        if (p == 0)
            return false;
    }
    return trie[p].flag;
}

int *base, *check, da_root = 1;
int getBaseValue(int root, int *base, int *check)
{
    int b = 1, flag = 0;
    while (flag == 0)
    {
        flag = 1;
        b += 1;
        for (int i = 0; i < BASE; i++)
        {
            if (trie[root].next[i] == 0) //边空
                continue;
            if (check[b + i] == 0)  //期待对应位置空
                continue;
            flag = 0;
            break;
        }
    }
    return b;
}
int ConvertToDoubleArrayTrie(int root, int da_root, int *base, int *check)
{
    if (root == 0)
        return 0;
    int max_ind = da_root;
    base[da_root] = getBaseValue(root, base, check);
    for (int i = 0; i < BASE; i++)
    {
        if (trie[root].next[i] == 0)
            continue;                                           
        check[base[da_root] + i] = da_root; // 检查dna check数组的正负--词的存在与否 base数组记录的值+i==child
        if (trie[trie[root].next[i]].flag)
        {
            check[base[da_root] + i] = -da_root;//负值代表成词
        }
    }
    for (int i = 0; i < BASE; i++)
    {

        if (trie[root].next[i] == 0)
            continue;
        max_ind = max(max_ind, ConvertToDoubleArrayTrie(trie[root].next[i], base[da_root] + i,
                                                        base, check));
    }
    return max_ind;
}
int main()
{
    // Trie t;
    cout << "trie version 4" << endl;
    clearTrie();
    int n;
    cin >> n;
    // int op;
    string s;
    // while (cin >> op >> s)
    // {
    //     switch (op)
    //     {
    //     case 1:
    //         t.insert(s);
    //         break;
    //     case 2:
    //         cout << "search word = " << s << ", result : " << t.search(s) << endl;
    //         break;
    //     }
    // }
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        // t.insert(s);
        insert(s);
    }
    // t.output();
    base = new int[MAX_COUNT];
    check = new int[MAX_COUNT];
    memset(base, 0, sizeof(int) * MAX_COUNT);
    memset(check, 0, sizeof(int) * MAX_COUNT);
    int max_ind = ConvertToDoubleArrayTrie(root, da_root, base, check);
    printf("trie usage : %lu byte\n", cnt * sizeof(node));
    printf("double array trie usage : %lu byte\n", (max_ind + 1) * sizeof(int));
    return 0;
}
