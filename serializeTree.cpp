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
// 二叉查找树前序遍历收集到的节点-.>node_vec中， 按照顺序重新建立，完全一样。
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void BST_insert(TreeNode *node, TreeNode *insert_node)
{
    if (insert_node->val < node->val)
    {
        if (node->left)
        {
            BST_insert(node->left, insert_node);
        }
        else
        {
            node->left = insert_node;
        }
    }
    else
    {
        if (node->right)
        {
            BST_insert(node->right, insert_node);
        }
        else
        {
            node->right = insert_node;
        }
    }
}
void change_int_to_string(int val, string &str_val)
{
    string tmp;
    while (val)
    {
        tmp += val % 10 + '0';
        val = val / 10;
    }
    for (int i = tmp.length() - 1; i >= 0; i--)
    {
        str_val += tmp[i];
    }
    str_val += '#';
}

void BST_preorder(TreeNode *node, string &data)
{
    if (!node)
    {
        return;
    }
    string str_val;
    change_int_to_string(node->val, str_val);
    data += str_val;
    BST_preorder(node->left, data);
    BST_preorder(node->right, data);
}

string serialize(TreeNode *root)
{
    string data;
    BST_preorder(root, data);
    return data;
}
TreeNode *deserialize(string data)
{
    if (data.length() == 0)
    {
        return NULL;
    }
    vector<TreeNode *> node_vec;
    int val = 0;
    for (int i = 0; i < data.length(); i++)
    {
        if (data[i] == '#')
        {
            node_vec.push_back(new TreeNode(val));
            val = 0;
        }
        else
        {
            val = val * 10 + data[i] - '0';
        }
    }
    for (int i = 1; i < node_vec.size(); i++)
    {
        BST_insert(node_vec[0], node_vec[i]);
    }
    return node_vec[0];
}
void preorder_print(TreeNode *node, int layer)
{
    if (!node)
    {
        return;
    }
    for (int i = 0; i < layer; i++)
    {
        printf("-----");
    }
    printf("[%d]\n", node->val);
    preorder_print(node->left, layer + 1);
    preorder_print(node->right, layer + 1);
}
int main()
{
    TreeNode root(8); //以8为根的二叉树
    vector<TreeNode *> node_vec;
    int test[] = {3, 10, 1, 6, 15};
    for (int i = 0; i < 5; i++)
    {
        node_vec.push_back(new TreeNode(test[i]));
    }
    for (int i = 0; i < node_vec.size(); i++)
    {
        BST_insert(&root, node_vec[i]);
    }
    cout << "=== === === preoder_tree_print === === ===" << endl;
    preorder_print(&root, 0);
    printf("\n");
    cout << "=== === === serialize_tree_data === === ===" << endl;
    string serialize_data = serialize(&root);
    cout << serialize_data << endl;
    printf("\n");
    cout << "=== === === deserialize_tree_data === === ===" << endl;
    TreeNode *deserialize_root = deserialize(serialize_data);
    preorder_print(deserialize_root, 0);
    // string str = "123#456#10000#1#";
    // int val = 0;
    // for (int i = 0; i < str.length(); i++)
    // {
    //     if (str[i] == '#')
    //     {
    //         printf("val = %d \n", val);
    //         val = 0;
    //     }
    //     else
    //     {
    //         val = val * 10 + str[i] - '0';
    //     }
    // }
    return 0;
}