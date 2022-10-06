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
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>
#include <time.h>
#include <math.h>
using namespace std;
#define NIL &(node::__NIL)
// 1 2 3 4 5 6 7 8 9
struct node
{
    node(int key = 0, int color = 0, node *lchild = NIL, node *rchild = NIL) : key(key), color(color), lchild(lchild), rchild(rchild) {}
    int key;
    int color; // 0 red, 1black
    node *lchild, *rchild;
    static node __NIL;
};
node node::__NIL(0, 1);

node *getNewNode(int key)
{
    return new node(key);
}
bool has_red_child(node *root)
{
    return root->lchild->color == 0 || root->rchild->color == 0;
}
node *left_rotate(node *root)
{
    node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}
node *right_rotate(node *root)
{
    node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

node *insert_maintain(node *root)
{
    // 插入站在祖父节点， 删除父亲节点
    int flag = 0;
    if (root->lchild->color == 0 && has_red_child(root->lchild))
        flag = 1;
    if (root->rchild->color == 0 && has_red_child(root->rchild))
        flag = 2;
    if (flag == 0)
        return root;
    if (root->lchild->color == 0 && root->rchild->color == 0)
    {
        root->color = 0;
        root->lchild->color = root->rchild->color = 1;
        return root;
    }
    if (flag == 1)
    {
        if (root->lchild->rchild->color == 0)
        {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    }
    else
    {
        if (root->rchild->lchild->color == 0)
        {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    root->color = 0;
    root->lchild->color = root->rchild->color = 1;
    return root;
}

node *__insert(node *root, int key)
{
    if (root == NIL)
        return getNewNode(key);
    if (key == root->key)
        return root;
    if (key < root->key)
    {
        root->lchild = __insert(root->lchild, key);
    }
    else
    {
        root->rchild = __insert(root->rchild, key);
    }
    return insert_maintain(root);
}

node *insert(node *root, int key)
{
    root = __insert(root, key);
    root->color = 1;
    return root;
}

node *erase_maintain(node *root)
{
    if (root->lchild->color != 2 && root->rchild->color != 2)
        return root;
    int flag = 0;
    if (has_red_child(root))
    {
        root->color = 0;
        if (root->lchild->color == 0)
        {
            root = right_rotate(root);
            flag = 1;
        }
        else
        {
            root = left_rotate(root);
            flag = 2;
        }
        root->color = 1;
        if (flag == 1)
            root->rchild = erase_maintain(root->rchild);
        else
            root->lchild = erase_maintain(root->lchild);
        return root;
    }
    if ((root->lchild->color == 1 && !has_red_child(root->lchild)) || (root->rchild->color == 1 && !has_red_child(root->rchild)))
    {
        root->lchild->color -= 1;
        root->rchild->color -= 1;
        root->color += 1;
        return root;
    }
    if (root->lchild->color == 1)
    {
        root->rchild->color = 1;
        if (root->lchild->lchild->color != 0)
        {
            root->lchild->color = 0;
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = 1;
        }
        root->lchild->color = root->color;
        root = right_rotate(root);
    }
    else
    {
        root->lchild->color = 1;
        if (root->rchild->rchild->color != 0)
        {
            root->rchild->color = 0;
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = 1;
        }
        root->rchild->color = root->color;
        root = left_rotate(root);
    }
    root->lchild->color = root->rchild->color = 1;
    return root;
}

node *predecessor(node *root)
{
    node *temp = root->lchild;
    while (temp->rchild != NIL)
        temp = temp->rchild;
    return temp;
}

node *__erase(node *root, int key)
{
    if (root == NIL)
        return root;
    if (key < root->key)
    {
        root->lchild = __erase(root->lchild, key);
    }
    else if (key > root->key)
    {
        root->rchild = __erase(root->rchild, key);
    }
    else
    {
        if (root->lchild == NIL || root->rchild == NIL)
        {
            node *temp = root->lchild == NIL ? root->rchild : root->lchild;
            temp->color += root->color;
            delete root;
            return temp;
        }
        else
        {
            node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}

node *erase(node *root, int key)
{
    root = __erase(root, key);
    root->color = 1;
    return root;
}
void clear(node *root)
{
    if (root == NIL)
        return;
    clear(root->lchild);
    clear(root->rchild);
    delete root;
    return;
}

void print(node *root)
{
    printf("(%d | %d, %d, %d )\n",
           root->color, root->key,
           root->lchild->key, root->rchild->key);
    return;
}
void output(node *root)
{
    if (root == NIL)
        return;
    print(root);
    output(root->lchild);
    output(root->rchild);
    return;
}

int main()
{
    int op, val;
    node *root = NIL;
    while (cin >> op>> val)
    {
        switch(op){
            case 1: root= insert(root,val); break;
            case 2: root = erase(root,val); break;
        }
        // root = insert(root, val);
        cout << endl
             << "==== rbtree print ====" << endl;
        output(root);
        cout << "==== rbtree print done ====" << endl;
    }
    return 0;
}

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode *left, TreeNode *right) : val(val), left(left), right(right) {}
};
//分裂一个二叉树，让子树和的乘积最大
class maxPro
{
    int avg, ans = 0;

    int getTotal(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        int val = root->val + getTotal(root->left) + getTotal(root->right);
        if (abs(val - avg) < abs(ans - avg))
            ans = val;
        return val;
    }
    int maxProduct(TreeNode *root)
    {
        int total = getTotal(root);
        avg = total / 2;
        ans = total;
        getTotal(root);
        return (long long)(ans) * (total - ans) % (long long)(1e9 + 7);
    }
};

class TimeMap
{
public:
    TimeMap() {}
    unordered_map<string, map<int, string>> h;
    void set(string key, string value, int timestamp)
    {
        h[key][timestamp] = value;
        return;
    }
    string get(string key, int timestamp)
    {
        if (h.find(key) == h.end())
            return "";
        if (h[key].find(timestamp) != h[key].end())
            return h[key][timestamp];
        h[key].insert(pair<int, string>(timestamp, ""));
        auto iter = h[key].find(timestamp);
        string ret = (--iter)->second;
        h[key].erase(h[key].find(timestamp));
        return ret;
    }
};
class flipMatch
{
    int ind;
    bool preorder(TreeNode *root, vector<int> &voyage, vector<int> &ret)
    {
        if (root == nullptr)
            return true;
        if (voyage[ind] != root->val)
        {
            ret.clear();
            ret.push_back(-1);
            return false;
        }
        ind += 1;
        if (ind + 1 == voyage.size())
            return true;
        if (root->left && root->left->val != voyage[ind])
        {
            swap(root->left, root->right);
            ret.push_back(root->val);
        }
        if (!preorder(root->left, voyage, ret))
            return false;
        if (!preorder(root->right, voyage, ret))
            return false;
        return true;
    }
    vector<int> flipMatchVoyage(TreeNode *root, vector<int> &voyage)
    {
        vector<int> ret;
        ind = 0;
        preorder(root, voyage, ret);
        return ret;
    }
};

// 连接每一层
class Node
{

    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int val) : val(val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int val, Node *left, Node *right, Node *next) : val(val), left(left), right(right), next(next) {}

    Node *layer_connect(Node *head)
    {
        Node *p = head, *pre = nullptr, *new_head = nullptr;
        while (p)
        {
            if (p->left)
            {
                if (pre)
                    pre->next = p->left;
                pre = p->left;
            }
            if (new_head == nullptr)
                new_head = pre;
            if (p->right)
            {
                if (pre)
                    pre->next = p->right;
                pre = p->right;
            }
            if (new_head == nullptr)
                new_head = pre;
            p = p->next;
        }
        return new_head;
    }

    Node *connect(Node *root)
    {
        Node *p = root;
        while (p == layer_connect(p))
            ; //返回下一层的头
        return root;
    }
};
class inorderSuc
{
    TreeNode *pre, *ans;
    bool inorder(TreeNode *root, TreeNode *p)
    {
        if (root == nullptr)
            return false;
        if (inorder(root->left, p))
            return true;
        if (pre == p)
        {
            ans = root;
            return true;
        }
        pre = root;
        if (inorder(root->right, p))
            return true;
    }
    // 找中序后继
    TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p)
    {
        pre = ans = nullptr;
        inorder(root, p);
        return ans;
    }
};
