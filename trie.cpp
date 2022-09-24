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
class node
{
public:
    node()
    {
        flag = false;
        for (int i = 0; i < BASE; i++)
            next[i] = nullptr;
    }
    bool flag;
    node *next[BASE];
};

class Trie
{

public:
    Trie()
    {
        root = new node();
    }
    bool insert(string word)
    {
        node *p = root;
        for (auto x : word)
        {
            int ind = x - 'a';
            if (p->next[ind] == nullptr)
                p->next[ind] = new node();
            p = p->next[ind];
        }
        if (p->flag)
            return false;
        p->flag = true;
    }

    bool search(string word)
    {
        node *p = root;
        for (auto x : word)
        {
            int ind = x - 'a';
            p = p->next[ind];
            if (p == nullptr)
                return false;
        }
        return p->flag;
    }
    static void __output(node *root, string s)
    {
        if (root == nullptr)
            return;
        if (root->flag)
            cout << "find : " << s << endl;
        for (int i = 0; i < BASE; i++)
        {
            __output(root->next[i], s + char(i + 'a'));
        }
    }
    void output()
    {
        __output(root, "");
        return;
    }
    static void clearTrie(node *root)
    {
        if (root == nullptr)
            return;
        for (int i = 0; i < BASE; i++)
            clearTrie(root->next[i]);
        delete root;
        return;
    }
    ~Trie()
    {
        clearTrie(root);
    }

private:
    node *root;
};

int main()
{
    Trie t;
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
    for(int i = 0; i <n ;i ++){
        cin >> s;
        t.insert(s);
    }
    t.output();
    return 0;
}