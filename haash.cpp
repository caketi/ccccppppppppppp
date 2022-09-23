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

class Node
{
public:
    Node(string data = "", Node *next = nullptr) : data(), next(nullptr) {}
    string data;
    Node *next;
    void insert(Node *node)
    {
        node->next = this->next;
        this->next = node;
        return;
    }
};

class HashTable
{
public:
    HashTable(int n = 100) : /*flag(n)*/ data(n), cnt(0) {}
    void insert(string s)
    {
        int ind = hash_func(s) % data.size();
        recalc_ind(ind, s);
        Node *p = &data[ind];
        while (p->next && p->next->data != s)
            p = p->next;
        if (p->next == nullptr)
        {
            p->insert(new Node(s));
            cnt += 1;
            if (cnt > data.size() * 3)
                expand();
        }
        // if (flag[ind] == false)
        // {
        //     data[ind] = s;
        //     flag[ind] = true;
        //     cnt += 1;
        //     if( cnt * 100 > data.size() * 75){
        //         expand();
        //     }
        // } else if (data[ind] != s){
        //     buff.insert(s);
        // }

        return;
    }
    bool find(string s)
    {
        int ind = hash_func(s) % data.size();
        recalc_ind(ind, s);
        Node *p = data[ind].next;
        while (p && p->data != s)
            p = p->next;
        return p != nullptr;
        // if(flag[ind] == false) return false;
        // if(data[ind] == s) return true;
        // return buff.find(s)!=buff.end();
        // return flag[ind];
    }

private:
    int cnt;
    vector<Node> data;
    // vector<string> data;
    // vector<bool> flag;
    // set<string> buff; // 公共缓冲区

    void expand()
    {
        int n = data.size() * 2;
        HashTable h(n);
        for (int i = 0; i < data.size(); i++)
        {
            Node *p = data[i].next;
            while (p)
            {
                h.insert(p->data);
                p = p->next;
            }
        }

        // for (int i = 0; i < data.size(); i++)
        // {
        //     if (flag[i] == false)
        //         continue;
        //     h.insert(data[i]);
        // }
        // for(auto x : buff){
        //     h.insert(x);
        // }
        *this = h;
        return;
    }
    int hash_func(string &s)
    {
        int seed = 131, hash = 0;
        for (int i = 0; s[i]; i++)
        {
            hash = hash * seed + s[i];
        }
        return hash & 0x7fffffff;
    }
    void recalc_ind(int &ind, string &s)
    {
        // int t = 1;
        // while (flag[ind] && data[ind] != s)
        // {
        //     ind += t * t;
        //     t += 1;
        //     ind %= data.size();
        // }
        // return;
    }
};

int main()
{
    int op;
    string s;
    HashTable h;
    while (cin >> op >> s)
    {
        switch (op)
        {
        case 1:
            h.insert(s);
            break;
        case 2:
            cout << "find " << s << " : " << h.find(s) << endl;
            break;
        }
    }
}

//  设计哈希集合
// class Nod
// {
// public:
//     Nod(int key = 0, Nod *next = nullptr) : key(key), next(next) {}
//     int key;
//     Nod *next;
//     void insert_after(Nod *node)
//     {
//         node->next = this->next;
//         this->next = node;
//         return;
//     }
//     void remove_after()
//     {
//         if (this->next == nullptr)
//             return;
//         Nod *p = this->next;
//         this->next = this->next->next;
//         delete p;
//         return;
//     }
// };
// class MyHashSet
// {
// public:
//     vector<Nod > data;
//     MyHashSet() : data(100) {}

//     int hash_func(int key) { return key & 0x7fffffff; }
//     void add(int key)
//     {
//         if (contains(key))
//             return;
//         int ind = hash_func(key) % data.size();
//         data[ind].insert_after(new Nod(key));
//         return;
//     }
//     void remove(int key)
//     {
//         int ind = hash_func(key) % data.size();
//         Nod *p = &data[ind];
//         while (p->next && p->next->key != key)
//             p = p->next;
//         p->remove_after();
//         return;
//     }

//     bool contains(int key)
//     {
//         int ind = hash_func(key) % data.size();
//         Nod *p = data[ind].next;
//         while (p && p->key != key)
//             p = p->next;
//         return p != nullptr;
//     }
// };

// 设计哈希映射
class Nd
{
public:
    Nd(int key = 0, int value = 0, Nd *next = nullptr) : key(key), value(value), next(next) {}
    int key, value;
    Nd *next;
    void insert_after(Nd *node)
    {
        node->next = this->next;
        this->next = node;
        return;
    }
    void remove_after()
    {
        if (this->next == nullptr)
            return;
        Nd *p = this->next;
        this->next = this->next->next;
        delete p;
        return;
    }
};
class MHashM
{
    vector<Nd> data;
    MHashM() : data(100) {}
    int hash_func(int key) { return key & 0x7fffffff; }
    void put(int key, int value)
    {
        int ind = hash_func(key) % data.size();
        Nd *p = &data[ind];
        while (p->next && p->next->key != key)
            p = p->next;
        if (p->next)
        {
            p->next->value = value;
        }
        else
        {
            p->insert_after(new Nd(key, value));
        }
        return;
    }
    int get(int key)
    {
        int ind = hash_func(key) % data.size();
        Nd *p = data[ind].next;
        while (p && p->key != key)
            p = p->next;
        return p->value;
    }
    void remove(int key)
    {
        int ind = hash_func(key) % data.size();
        Nd *p = &data[ind];
        while (p->next && p->next->key != key)
            p = p->next;
        p->remove_after();
        return;
    }
};

// LRU hash linked list
class Nod
{
public:
    int key, value;
    Nod *next, *prev;
    Nod(int key = 0, int value = 0, Nod *prev = nullptr, Nod *next = nullptr)
        : key(key), value(value), prev(prev), next(next) {}
    Nod *remove_this()
    {
        if (this->prev)
            this->prev->next = this->next;
        if (this->next)
            this->next->prev = this->prev;
        this->prev = this->next = nullptr;
        return this;
    }
    void insert_prev(Nod *node)
    {
        node->next = this;
        node->prev = this->prev;
        if (this->prev)
            this->prev->next = node;
        this->prev = node;
        return;
    }
};
class HashList
{

public:
    int capacity;
    Nod head, tail;
    unordered_map<int, Nod *> data;
    HashList(int capacity) : capacity(capacity)
    {
        head.next = &tail;
        tail.prev = &head;
    }
    void put(int key, int value)
    {
        if (data.find(key) != data.end())
        {
            data[key]->value = value;
            data[key]->remove_this();
        }
        else
        {
            data[key] = new Nod(key, value);
        }
        tail.insert_prev(data[key]);
        if (data.size() > capacity)
        {
            data.erase(data.find(head.next->key));
            delete head.next->remove_this();
        }
        return;
    }
    int get(int key)
    {
        if (data.find(key) == data.end())
            return -1;
        data[key]->remove_this();
        tail.insert_prev(data[key]);
        return data[key]->value;
    }
};
class LRUCache
{
public:
    HashList h;
    LRUCache(int capacity) : h(capacity) {}
    int get(int key)
    {
        return h.get(key);
    }
    void put(int key, int value)
    {
        h.put(key, value);
        return;
    }
};
// tinyUrl longUrl
//  0-25 'a-z' 26-51 'A-Z' 52-61 '0'-'9'
char ch(int x)
{
    x %= 62;
    if (x < 26)
        return x + 'a';
    if (x < 52)
        return x - 26 + 'A';
    return x - 52 + '0';
}
string rand_string(int n)
{
    string s = "";
    for (int i = 0; i < n; i++)
    {
        s += ch(rand());
    }
    return s;
}

unordered_map<string, string> h;
string endcode(string longUrl)
{
    string s;
    do
    {
        s = rand_string(5);
    } while (h.find(s) != h.end());
    h[s] = longUrl;
    return s;
}
string decode(string shortUrl)
{
    return h[shortUrl];
}
// len = 10 , 在s中出现次数超过一次
vector<string> findRepeatedDnaSequences(string s)
{
    unordered_map<string, int> h;
    for (int i = 0, I = s.size() - 9; i < I; i++)
    { // 要求字串长度10
        h[s.substr(i, 10)] += 1;
    }
    vector<string> ret;
    for (auto x : h)
    {
        if (x.second == 1)
            continue;
        ret.push_back(x.first);
    }
    return ret;
}
// 最大单次长度乘积
int maxProduct(vector<string> &words)
{
    vector<int> mark(words.size());
    for (int i = 0; i < words.size(); i++)
    {
        for (auto c : words[i])
        {
            mark[i] |= (1 << (c - 'a')); //对应字母映射标记1
        }
    }
    int ans = 0;
    for (int i = 0; i < words.size(); i++)
    {
        for (int j = i + 1; j < words.size(); j++)
        {
            if (mark[i] & mark[j]) // 比较26位向量
                continue;
            ans = max(ans, int(words[i].size() * words[j].size()));
        }
    }
    return ans;
}

// 搜索     1 4 7 11 15
//          2 5 8 12 19
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int i = 0, j = matrix[0].size() - 1;
    while (i < matrix.size() && j >= 0)
    {
        if (matrix[i][j] == target)
            return true;
        if (matrix[i][j] < target)
            i += 1;
        else
            j -= 1;
    }
}
// 979.leeecode
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(nullptr), right(nullptr) {}
};

// 节点数量-硬币数量 n-m
int getResult(TreeNode *root, int &n, int &m)
{
    n = m = 0;
    if (root == nullptr)
        return 0;
    n = 1, m = root->val;
    int ans = 0, n1, m1;
    ans += getResult(root->left, n1, m1);
    ans += abs(n1 - m1);
    n += n1, m += m1;
    ans += getResult(root->right, n1, m1);
    ans += abs(n1 - m1);
    n += n1, m += m1;
    return ans;
}
int distributeCoins(TreeNode *root)
{
    int n, m;
    return getResult(root, n, m);
}

// p q
//  k->....
class Noood
{
public:
    int val;
    Noood *prev;
    Noood *next;
    Noood *child;
};
Noood *flatten(Noood *head)
{
    Noood *p = head, *q, *k;
    while (p)
    {
        if (p->child)
        {
            q = p->next;
            k = flatten(p->child); //扁平化
            p->next = k;
            k->prev = p;
            while (p->next)
                p = p->next;
            p->next = q;
            if (q)
                q->prev = p;
        }
        p = p->next; // p->child == null
    }
    return head;
}

void dfs(TreeNode *root, int c, int k, vector<int> &ret)
{
    if (root == nullptr)
        return;
    if (c == k) 
    {
        ret.push_back(root->val);
        return;
    }
    dfs(root->left, c + 1, k, ret);
    dfs(root->right, c + 1, k, ret);
    return;
}
TreeNode *getResult(TreeNode *root, TreeNode *target, int &k, vector<int> &ret)
{
    if (root == nullptr)
        return nullptr;
    if (root == target)
    {
        dfs(root, 0, k, ret);
        return root;
    }
    if (getResult(root->left, target, k, ret))
    {
        k -= 1;  // k==1 ?
        if (k == 0)
            ret.push_back(root->val);
        dfs(root->right, 0, k - 1, ret); // k>1, dfs() k==2? 回溯 猎空shift e
        return target;
    }
    else if (getResult(root->right, target, k, ret))
    {
        k -= 1;
        if (k == 0)
            ret.push_back(root->val);
        dfs(root->left, 0, k - 1, ret);
        return target;
    }
    return nullptr;
}
vector<int> distanceK(TreeNode *root, TreeNode *target, int k)
{
    vector<int> ret;
    getResult(root, target, k, ret);
}




class RandomizedSet{
    public :
    unordered_map<int,int> h;
    vector<int> arr;
    RandomizedSet(){
        srand(time(0));
    }

    bool insert(int val){
        if(h.find(val) != h.end()) return false;
        h[val] = arr.size(); //arr尾插,
        arr.push_back(val);
        return true;
    }

    void swap_item(int i , int j){
        swap(arr[i], arr[j]);
        h[arr[i]] = i;
        h[arr[j]] = j;
    }
    bool remove(int val){
        if(h.find(val) == h.end()) return false;
        int n = h[val], m = arr.size()-1;
        swap_item(n, m);
        h.erase(h.find(val));
        arr.pop_back();
        return true;
    }
    int getRandom(){
        return arr[rand() % arr.size()];
    }
};