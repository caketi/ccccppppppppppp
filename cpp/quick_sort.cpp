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
using namespace std;

//769. [4,3,2,1,0] -- 1  分割成若干块，并对每块单独排序，连接起来后，结果和原数组的升序一致
int maxChunkToSorted(vector<int>& arr){
    int n =arr.size();
    int m = 0;
    int res = 0;
    for(int i = 0; i < n; i++){
        m = max(m, arr[i]);
        if(m == i){
            res++;
        }
    }
    return res;
}

const int maxn = 2e5 + 10;
const int inf = 0x3f3f3f3f;
const int threshold = 16;
inline int getmid(int a, int b, int c)
{
    if (a > b)
        swap(a, b);
    if (a > c)
        swap(a, c);
    if (b > c)
        swap(a, c);
    return b;
}

void __quick_sort_v3(int *arr, int l, int r)
{
    while (r - l > threshold)
    {
        int x = l, y = r, base = getmid(arr[l], arr[(l + r) / 2], arr[r]);
        do
        {
            while (arr[x] < base)
                x++;
            while (arr[y] > base)
                y--;
            if (x <= y)
            {
                swap(arr[x], arr[y]);
                x++, y--;
            }
        } while (x <= y);
        __quick_sort_v3(arr, x, r);
        r = y;
    }
    return;
}

void final_insert_sort(int *arr, int l, int r)
{
    int ind = l;
    for (int i = l + 1; i <= r; i++)
    {
        if (arr[i] < arr[ind])
            ind = i;
    } // 找到最小值索引
    while (ind > l)
    {
        swap(arr[ind], arr[ind - 1]);
        ind--;
    }
    for (int i = l + 2; i <= r; i++)
    {
        int j = i;
        while (arr[j] < arr[j - 1])
        {
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
    return;
}

void quick_sort_v1(int *arr, int l, int r)
{
    if (l >= r)
        return;

    int x = l, y = r, base = arr[l];
    while (x < y)
    {
        while (x < y && arr[y] >= base)
            y--;
        if (x < y) // 找到第一个小于的元素
            arr[x++] = arr[y];
        while (x < y && arr[x] < base)
            x++;
        if (x < y)
            arr[y--] = arr[x];
    }
    arr[x] = base; // x == y  小 base(x==y) 大
    quick_sort_v1(arr, l, x - 1);
    quick_sort_v1(arr, x + 1, r);
    return;
}

void quick_sort_v2(int *arr, int l, int r)
{
    while (l < r)
    {
        int x = l, y = r, base = arr[l];
        while (x < y)
        {
            while (x < y && arr[y] >= base)
                y--;
            if (x < y)
                arr[x++] = arr[y];
            while (x < y && arr[x] < base)
                x++;
            if (x < y)
                arr[y--] = arr[x];
        }
        arr[x] = base;
        quick_sort_v2(arr, x + 1, r);
        r = x - 1;
    }
    return;
}

void quick_sort_v3(int *arr, int l, int r)
{
    __quick_sort_v3(arr, l, r);
    final_insert_sort(arr, l, r);
}

// 3[a] === aaa 2[bc] === bcbc

string decodeString(string s)
{
    string res = "";
    stack<int> nums;
    stack<string> strs;
    int num = 0;
    int len = s.size();
    for (int i = 0; i < len; ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            num = num * 10 + s[i] - '0';
        }
        else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            res = res + s[i];
        }
        else if (s[i] == '[') //将‘[’前的数字压入nums栈内， 字母字符串压入strs栈内
        {
            nums.push(num);
            num = 0;
            strs.push(res);
            res = "";
        }
        else //遇到‘]’时，操作与之相配的‘[’之间的字符，使用分配律
        {
            int times = nums.top();
            nums.pop();
            for (int j = 0; j < times; ++j)
                strs.top() += res;
            res = strs.top(); //之后若还是字母，就会直接加到res之后，因为它们是同一级的运算
                              //若是左括号，res会被压入strs栈，作为上一层的运算
            strs.pop();
        }
    }
    return res;
}

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// 生产不同的二叉树
vector<TreeNode *> dfs(int l, int r)
{
    vector<TreeNode *> ans;
    if (l > r)
    {
        ans.push_back(nullptr);
        return ans;
    }
    for (int i = l; i <= r; i++)
    {
        vector<TreeNode *> left_tree = dfs(l, i - 1);
        vector<TreeNode *> right_tree = dfs(i + 1, r);
        // eg : i = 3
        for (TreeNode *left : left_tree)
        { // {1, null ,2} { 2, 1,null}
            for (TreeNode *right : right_tree)
            { //{4}
                TreeNode *t = new TreeNode(i, left, right);
                ans.push_back(t);
            }
        }
    }
    return ans;
}
vector<TreeNode *> generateTrees(int n)
{
    vector<TreeNode *> ans;
    if (n == 0)
        return ans;
    return dfs(1, n);
}

// 最小k个数
void quick_select(vector<int> &arr, int l, int r, int k)
{
    if (l >= r)
        return;
    int x = l, y = r, mid = getmid(arr[l], arr[(l + r) / 2], arr[r]);
    do
    {
        while (arr[x] < mid)
            x++;
        while (arr[y] > mid)
            y--;
        if (x <= y)
        {
            swap(arr[x], arr[y]);
            x++, y--;
        }
    } while (x <= y);
    if (y - l == k - 1)
        return;
    if (y - l >= k)
    {
        quick_select(arr, l, y, k);
    }
    else
    {
        quick_select(arr, x, r, k - x + l);
    }
    return;
}
vector<int> smallestK(vector<int> &arr, int k)
{
    vector<int> ans;
    if (k == 0)
        return ans;
    quick_select(arr, 0, arr.size() - 1, k);
    while (k)
        ans.push_back(arr[--k]);
    return ans;
}
// 奇数位于偶数前面
vector<int> exchange(vector<int> &nums)
{
    if (nums.size() == 0)
        return nums;
    int x = 0, y = nums.size() - 1;
    do
    {
        while (x < nums.size() && nums[x] % 2)
        {
            x++;
        }
        while (y >= 0 && nums[y] % 2 == 0)
        {
            y--;
        }
        if (x <= y)
        { // 漏网之鱼非奇非偶
            swap(nums[x], nums[y]);
            x++, y--;
        }
    } while (x <= y);
    return nums;
}
// 0 1 2
// 不同颜色
void three_partition(vector<int> &arr, int l, int r, int mid)
{
    if (l >= r)
        return;
    int x = -1, y = r + 1, i = 1;
    while (i < y)
    {
        if (arr[i] == mid)
        {
            i++;
        }
        else if (arr[i] < mid)
        {
            x++;
            swap(arr[x], arr[i]);
            i++;
        }
        else if (arr[i] > mid)
        {
            y--;
            swap(arr[y], arr[i]);
        }
    }
}

void sortColors(vector<int> &arr)
{
    three_partition(arr, 0, arr.size() - 1, 1);
    return;
}
int main(int argc, char *argv[])
{
    // int arr[10] = {3, 1, 4, 5, 9, 10};
    // quick_sort_v1(arr, 0, 6);

    // for (int i = 0; i < 7; i++)
    // {
    //     cout << arr[i] << " ";
    // }
    string s = "3[a]2[bc]";
    string res = decodeString(s);
    cout << res;
    return 0;
}