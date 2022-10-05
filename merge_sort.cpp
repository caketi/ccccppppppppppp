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
#include <assert.h>
using namespace std;



struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
};
//  k---深度， max_K 最大深度
void getResult(TreeNode *root, int k, int &max_k, int &ans){
    if(root == nullptr) return;
    if(k == max_k) ans+= root->val;
    if(k > max_k){
        max_k = k;
        ans = root->val;
    }
    getResult(root->left, k+1, max_k, ans);
    getResult(root->right, k+1, max_k, ans);
    return ;
}

int deepestLeavesSum(TreeNode* root){
    int max_k = 0, ans = 0;
    getResult(root, 1, max_k, ans);
    return ans;
}


// 首个公共祖先
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q){
    if(root == nullptr) return nullptr;
    if(root == p || root == q) return root;
    TreeNode *l = lowestCommonAncestor(root->left, p, q);
    TreeNode *r = lowestCommonAncestor(root->right, p, q);
    if(l != nullptr && r!= nullptr) return root;
    if(l != nullptr) return l;
    return r;
}

struct Data{
    Data(int i, int j, long long sum): i(i), j(j), sum(sum){}
    int i, j, sum;
};
struct CMP{
    bool operator()(const Data &a, const Data &b){
        return a.sum > b.sum;
    }
};
int rangeSum(vector<int>& nums, int n, int left, int right){
    priority_queue<Data, vector<Data>, CMP> q;
    for(int i = 0; i < n; i++){
        q.push(Data{i, i, nums[i]});
    }
    int ans = 0, mod = 1e9 + 7;
    for(int i = 1; i <=right; i++){
        Data d  = q.top();
        q.pop();
        if(i >= left) ans = (ans+d.sum) % mod;
        if(d.j + 1 <n) q.push(Data{d.i, d.j+1, (d.sum+nums[d.j+1]) % mod});
    }
    return ans;
}


// nums = [5,2,6,1];
// [2,1,1,0]
// 5的右侧有2个小的。。。。
// struct Data
// {
//     Data(int val, int ind) : val(val), ind(ind), cnt(0) {}
//     bool operator>(const Data &a)
//     {
//         return val >= a.val;
//     }
//     int val, ind, cnt;
// };
// void mergeX(vector<Data> &arr, int l, int r)
// {
//     if (l >= r)
//         return;
//     int mid = (l + r) >> 1;
//     int k =l, p1 = l, p2 = mid + 1;
//     mergeX(arr, l, mid);
//     mergeX(arr, mid + 1, r);
//     while (p1 <= mid || p2 <= r)
//     {
//         if ((p2 > r) || (p1 < mid && arr[p1] > arr[p2]))
//         {
//             arr[p1].cnt += (r - p2 + 1);//右侧剩下的都是小雨的
//             temp[k++] = arr[p1++];
//         }
//         else
//         {
//             temp[k++] = arr[p2++];
//         }
//     }
//     for (int i = l; i <= r; i++)
//         arr[i] = temp[i];
//     return;
// }
// vector<Data> temp;
// vector<int> countSmaller(vector<int> &nums)
// {
//     vector<Data> arr;
//     for (auto x : nums)
//         arr.push_back(Data{nums[x], x});
//     while (temp.size() < arr.size())
//         temp.push_back(Data{0, 0});
//     mergeX(arr, 0, arr.size() - 1);
//     vector<int> ret(nums.size());
//     for (auto x : arr)
//         ret[x.ind] = x.cnt;
//     return ret;
// }

// 区间和 前缀和的两项相减
//  -2 5 -1
// 0 -2 3 2
// lower <= sum[j] - sum[i] <= upper  i<j
//  sum[j] - lower >= sum[i] >= sum[j] - upper
// a <= sum[i] <= b

int countTwoPart(vector<long long> &sum, int l1, int r1, int l2, int r2, int lower, int upper)
{
    int ans = 0, k1 = l1, k2 = l1;
    for (int j = l2; j <= r2; j++)
    {
        long long a = sum[j] - upper;
        long long b = sum[j] - lower;
        while (k1 <= r1 && sum[k1] < a)
            k1 += 1;
        while (k2 <= r2 && sum[k2] <= b)
            k2 += 1;
        ans += k2 - k1;
    }
    return ans;
}
vector<long long> temp1;
int mergeSort(vector<long long> &sum, int l, int r, int lower, int upper)
{
    if (l >= r)
        return 0;
    int mid = (l + r) >> 1, ans = 0;
    ans += mergeSort(sum, l, mid, lower, upper);
    ans += mergeSort(sum, mid + 1, r, lower, upper);
    ans += countTwoPart(sum, l, mid, mid + 1, r, lower, upper);
    int k = l, p1 = l, p2 = mid + 1;
    while (p1 <= mid || p2 <= r)
    {
        if ((p2 > r) || (p1 <= mid && sum[p1] <= sum[p2]))
        {
            temp1[k++] = sum[p1++];
        }
        else
        {
            temp1[k++] = sum[p2++];
        }
    }
    for (int i = l; i <= r; i++)
        sum[i] = temp1[i];
    return ans;
}
vector<long long> temp;
int countRangeSum(vector<int> &nums, int lower, int upper)
{
    vector<long long> sum(nums.size() + 1);
    while (temp.size() < sum.size())
        temp.push_back(0);
    sum[0] = 0;
    for (int i = 0; i < nums.size(); i++)
        sum[i + 1] = sum[i] + nums[i];
    return mergeSort(sum, 0, sum.size() - 1, lower, upper);
}

// void midfor(TreeNode* root, vector<int>& arr){
//     if(root == nullptr) return;
//     midfor(root->left, arr);
//     arr.push_back(root->val);
//     midfor(root->right, arr);
//     return ;
// }

// vector<int> getAllElements(TreeNode* root1, TreeNode* root2){
//     vector<int> lnums, rnums;
//     midfor(root1, lnums);
//     midfor(root2, rnums);
//     int p1 = 0, p2 =0;
//     vector<int> ret;
//     while(p1<lnums.size() || p2 < rnums.size()){
//         if((p2 >= rnums.size()) || (p1<lnums.size() && lnums[p1] <= rnums[p2]) ){
//             ret.push_back(lnums[p1++]);
//         }else {
//             ret.push_back(rnums[p2++]);
//         }
//     }
//     return ret;
// }

// 排序链表
// ListNode* mergeSort(ListNode* head, int n){
//     if(head == nullptr || head->next == nullptr) return head;
//     int l = n/2, r = n-l;
//     ListNode* lp =head, *rp = lp, *p;
//     for(int i = 1; i< l; i++, rp =rp->next);
//     p = rp, rp = rp->next;
//     p->next = nullptr;
//     lp = mergeSort(lp, l);
//     rp = mergeSort(rp, r);
//     ListNode ret;
//     p = &ret;
//     while(lp || rp){
//         if((rp == nullptr) || (lp && lp->val <= rp->val)){
//             p->next = lp;
//             lp = lp->next;
//             p = p->next;
//         } else {
//             p->next  = rp;
//             rp = rp->next;
//             p = p->next;
//         }
//     }
//     return ret.next;
// }

// ListNode* sortList(ListNode* head){
//     int n= 0;
//     ListNode* p = head;
//     while(p) p = p->next, n+=1;
//     return mergeSort(head, n);
// }
// 合并k个升序链表
// lists= [[1,4,5], [1,3,4]]
// struct CMP{
//     bool operator()(ListNode*p, ListNode *q){
//         return p->val > q->val;
//     }
// };
// ListNode* mergeKLists(vector<ListNode*>& lists){
//     priority_queue<ListNode*, vector<ListNode *>, CMP> q;
//     for(auto x:lists){
//         if( x==nullptr) continue;
//         q.push(x); // 压入头部
//     }
//     ListNode ret, *p = &ret;
//     while(!q.empty()){
//         ListNode* cur = q.top();
//         q.pop();
//         p->next = cur;
//         p = cur;
//         if(cur->next) q.push(cur->next);
//     }
//     return ret.next;
// }
//逆序数 [7,4.3] 3
vector<int> temp2;
int countResult(vector<int> &nums, int l, int r)
{
    if (l >= r)
        return 0;
    int ans = 0, mid = (l + r) >> 1;
    ans += countResult(nums, l, mid);
    ans += countResult(nums, mid + 1, r);
    int k = l, p1 = l, p2 = mid + 1;
    while (p1 <= mid || p2 <= r)
    {
        if ((p2 > r) || (p1 <= mid && nums[p1] <= nums[p2]))
        {
            temp2[k++] = nums[p1++];
        }
        else
        {
            temp2[k++] = nums[p2++];
            ans += (mid - p1 + 1);
        }
    }
    for (int i = l; i <= r; i++)
        nums[i] = temp2[i];
    return ans;
}
int reversePairs(vector<int> &nums)
{
    while (temp.size() < nums.size())
        temp.push_back(0);
    return countResult(nums, 0, nums.size() - 1);
}

void merge_sort(int *arr, int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));
    int k = 0, p1 = l, p2 = mid + 1;
    while (p1 <= mid || p2 <= r)
    {
        if ((p2 > r) || (p1 <= mid && arr[p1] <= arr[p2]))
        { //左边小或者右边空了
            temp[k] = arr[p1];
            k += 1, p1 += 1;
        }
        else
        {
            temp[k] = arr[p2];
            k += 1, p2 += 1;
        }
    }
    for (int i = l; i <= r; i++)
        arr[i] = temp[i - l];
    // temp-- 0
    // arr----l-r
    free(temp);
    return;
}
int main()
{
    int n;
    int arr[100];
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    merge_sort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}