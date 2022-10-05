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

// class node
// {
// public:
//     node()
//     {
//         flag = 0;
//         for (int i = 0; i < 26; i++)
//         {
//             next[i] = nullptr;
//         }
//     }
//     int flag;
//     node *next[26];
// };

// class Trie
// {
// public:
//     node *root;
//     Trie()
//     {
//         root = new node();
//     }
//     void insert(string word)
//     {
//         node *p = root;
//         for (auto x : word)
//         {
//             int ind = x - 'a';
//             if (p->next[ind] == nullptr)
//                 p->next[ind] = new node();
//             p->flag = true;
//             return;
//         }
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
//     bool startsWith(string prefix)
//     {
//         node *p = root;
//         for (auto x : prefix)
//         {
//             int ind = x - 'a';
//             p = p->next[ind];
//             if (p == nullptr)
//                 return false;
//         }
//         return true;
//     }
// };

// #define BASE 26
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
//     set<string> s;
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
//             p->s.insert(word);
//             if (p->s.size() > 3)
//             {
//                 auto iter = p->s.end();
//                 iter--;
//                 p->s.erase(iter);
//             }
//         }
//         if (p->flag)
//             return false;
//         p->flag = true;
//     }

//     vector<vector<string>> search(string word)
//     {
//         node *p = root;
//         vector<vector<string>> ret;
//         for (auto x : word)
//         {
//             if (p == nullptr)
//             {
//                 ret.push_back(vector<string>());
//                 continue;
//             }
//             int ind = x - 'a';
//             p = p->next[ind];
//             vector<string> temp;
//             if (p != nullptr)
//             {
//                 for (auto s : p->s)
//                     temp.push_back(s);
//             }
//             ret.push_back(temp);
//         }
//         return ret;
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

// vector<vector<string>> suggestProducts(vector<string>& products, string searchWord){
//     Trie tree;
//     for(auto s : products) tree.insert(s);
//     return tree.search(searchWord);
// }

#define BASE 2
class node
{
public:
    node()
    {
        for (int i = 0; i < BASE; i++)
            next[i] = nullptr;
    }
    node *next[BASE];
};

class Trie
{
public:
    Trie()
    {
        root = new node();
    }
    void insert(int x)
    {
        node *p = root;
        for (int i = 30; i >= 0; --i)
        {
            int ind = !!(x & (1 << i));
            if (p->next[ind] == nullptr)
                p->next[ind] = new node();
            p = p->next[ind];
        }
    }

    int search(int x)
    {
        node *p = root;
        int ans = 0;
        for (int i = 30; i >= 0; --i)
        {
            int ind = !!(x & (1 << i));
            if (p->next[!ind])
            {
                ans |= (1 << i);
                p = p->next[!ind];
            }
            else
            {
                p = p->next[ind];
            }
        }
        return ans;
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

int findMaximumXOR(vector<int> &nums)
{
    Trie tree;
    for (auto x : nums)
        tree.insert(x);
    int ans = 0;
    for (auto x : nums)
        ans = max(ans, tree.search(x));
    return ans;
}
int main()
{

    vector<int> ans = {1, 4};
    cout << findMaximumXOR(ans);

    return 0;
}

vector<int> diffWaysToCompute(string expression)
{
    vector<int> ret;
    for (int i = 0; expression[i]; i++)
    {
        char op = expression[i];
        if (op != '+' && op != '-' && op != '*')
            continue;
        string a_str = expression.substr(0, i);
        string b_str = expression.substr(i + 1, expression.size());
        cout << a_str << " " << b_str << endl;
        vector<int> a = diffWaysToCompute(a_str);
        vector<int> b = diffWaysToCompute(b_str);
        for (auto x : a)
        {
            for (auto y : b)
            {
                switch (op)
                {
                case '+':
                    ret.push_back(x + y);
                    break;
                case '-':
                    ret.push_back(x - y);
                    break;
                case '*':
                    ret.push_back(x * y);
                    break;
                }
            }
        }
        if (ret.size() == 0)
        {
            int num = 0;
            for (auto x : expression)
            {
                num = num * 10 + (x - '0');
            }
            ret.push_back(num);
        }
    }
    return ret;
}

class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node()
    {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int _val)
    {
        val = _val;
        neighbors = vector<Node *>();
    }
    Node(int _val, vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};
unordered_map<Node *, Node *> h;
Node *getResult(Node *node)
{
    if (node == nullptr)
        return nullptr;
    if (h[node])
        return h[node];
    h[node] = new Node(node->val);
    for (auto x : node->neighbors)
    {
        getResult(x);
        h[node]->neighbors.push_back(h[x]);
    }
    return h[node];
}

Node *cloneGraph(Node *node)
{
    h.clear();
    return getResult(node);
}

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

typedef pair<int, int> PII;
map<int, vector<PII>> hh;
void getResult(TreeNode *root, int i, int j)
{
    if (root == nullptr)
        return;
    hh[j].push_back(PII(i, root->val));
    getResult(root->left, i + 1, j - 1);
    getResult(root->left, i + 1, j + 1);
    return;
}
// [3,9,20,null,null,15,7]----[[9],[3,15],[20],[7]]
vector<vector<int>> verticalTraversal(TreeNode *root)
{
    hh.clear();
    getResult(root, 0, 0);
    vector<vector<int>> ret;
    for (auto item : hh)
    {
        vector<PII> &arr = item.second;
        sort(arr.begin(), arr.end());
        vector<int> temp;
        for (auto x : arr)
            temp.push_back(x.second);
        ret.push_back(temp);
    }
    return ret;
}