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

int main()
{
    set<int> h; // set底层二叉排序树，中序
    for (auto i = 0; i < 10; i++)
    {
        int val = rand() % 100;
        cout << "insert val = " << val << endl;
        h.insert(val);
        for (auto x : h)
        {
            cout << x << " ";
        }
        cout << endl;
        auto iter = h.find(val);
        if (iter == h.begin())
        {
            cout << val << " is first" << endl;
        }
        else
        {
            --iter;
            cout << *iter << " is the first biggest before " << val << endl;
        }
    }
    return 0;
}

class serializede
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    string serialize(TreeNode *root)
    {
        if (root == nullptr)
            return "";
        string ret = "";
        stringstream ss;
        ss << root->val;
        ss >> ret;
        if (root->left == nullptr && root->right == nullptr)
            return ret;
        ret += "(";
        ret += serialize(root->left);
        if (root->right)
        {
            ret += ",";
            ret += serialize(root->right);
        }
        ret += ")";
        cout << ret << endl;
        return ret;
    }
    TreeNode *deserialize(string data)
    {
        // 2 ( , ) 4中情况
        int scode = 0, ind = 0, k = 0;
        stack<TreeNode *> s;
        TreeNode *p, *root = nullptr;
        while (ind < data.size())
        {
            switch (scode)
            {
            case 0:
            {
                if (data[ind] <= '9' && data[ind] >= '0')
                    scode = 1;
                else if (data[ind] == '(')
                    scode = 2;
                else if (data[ind] == ',')
                    scode = 3;
                else if (data[ind] == ')')
                    scode = 4;
            }
            break;
            case 1:
            {
                int num = 0;
                while (ind < data.size() && data[ind] <= '9' && data[ind] >= '0')
                {
                    num = num * 10 + (data[ind] - '0');
                    ind += 1;
                }
                p = new TreeNode(num);
                if (root == nullptr)
                    root = p;
                if (k == 1)
                    s.top()->left = p; // k== 1 左子树
                else if (k == 2)
                    s.top()->right = p; // k==2 右子树
                scode = 0;
            }
            break;
            case 2:
            {
                s.push(p);
                ind += 1;
                k = 1;
                scode = 0;
            }
            break;
            case 3:
            {
                k = 2;
                ind += 1;
                scode = 0;
            }
            break;
            case 4:
            {
                s.pop();
                ind += 1;
                scode = 0;
            }
            break;
            }
        }
        return root;
    }
};
//[2,3,1]-- 找出未出现的最小整数
int firstMissingPosition(vector<int> &nums)
{
    for (int i = 0; i < nums.size(); i++)
    {
        while (nums[i] != i + 1)
        {
            if (nums[i] <= 0 || nums[i] > nums.size())
                break;
            int ind = nums[i] - 1;
            if (nums[i] == nums[ind])
                break;
            swap(nums[i], nums[ind]);
        }
    }
    int ind = 0;
    while (ind < nums.size() && nums[ind] == ind + 1)
        ++ind;
    return ind + 1;
}
vector<vector<int>> subsets(vector<int> &nums)
{
    int n = nums.size();
    unordered_map<int, int> mark;
    for (int i = 0, j = 1; i < 10; i++, j <<= 1)
        mark[j] = i;
    vector<vector<int>> ret;
    for (int i = 0, I = (1 << n); i < I; i++)
    {
        vector<int> arr;
        int val = i;
        while (val)
        {
            arr.push_back(nums[mark[val & (~val)]]);
            val &= (val - 1);
        }
        ret.push_back(arr);
    }
    return ret;
}

void delNum(map<long long, int> &h, long long x)
{
    h[x] -= 1;
    if (h[x] == 0)
        h.erase(h.find(x));
    return;
}
// abs(nums[i] - nums[j]) <= t  && abs(i - j) <= k  x-t [1,2,3,1] k = 3, t=0
bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t)
{
    map<long long, int> h;
    for (int i = 0; i < nums.size(); i++)
    {
        if (i > k)
        {
            delNum(h, nums[i - k - 1]);
        }
        h[(long long)(nums[i]) - t - 1] += 1;
        h[(long long)(nums[i]) - t + 1] += 1;
        auto iter = h.find((long long)(nums[i]) - t - 1);
        iter++;
        if (iter->first != (long long)(nums[i] + t + 1))
            return true;
        delNum(h, (long long)(nums[i]) - t - 1);
        delNum(h, (long long)(nums[i]) + t + 1);
        h[nums[i]] += 1;
    }
    return false;
}