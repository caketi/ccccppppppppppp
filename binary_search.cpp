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

int searchInsert(vector<int>& nums, int target){
    int index = -1;
    int begin = 0;
    int end = nums.size() -1; 
    while(index == -1){
        int mid = (begin+end) /2;
        if(target == nums[mid]){
            index = mid;
        }
        else if (target < nums[mid]){
            if(mid == 0 || target > nums[mid-1]){
                index  = mid;
            }
            end = mid - 1;
        }
        else if (target > nums[mid]){
            if(mid == nums.size()-1 || target< nums[mid+1]){
                index = mid + 1;
            }
            begin = mid + 1;
        }
    }
    return index;
}

// 数组： 下标-》值     映射 - 空间     互换
// 函数： 参数-》值     计算 - 时间
void output_binary_process(int *arr, int n, int head, int tail, int mid)
{
    int p1, p2, p3, len = 0;
    for (int i = 0; i < n; i++)
    {
        len += printf("%5d", i);
        if (i == head)
            p1 = len - 1;
        if (i == tail)
            p2 = len - 1;
        if (i == mid)
            p3 = len - 1;
    }
    printf("p1 = %d, p2= %d, p3=%d\n", p1, p2, p3);
    printf("\n");
    for (int i = 0; i < len; i++)
        printf("-");
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%5d", arr[i]);
    }
    printf("\n");
    for (int i = 0; i < len; i++)
    {
        if (i == p1 || i == p2 || i == p3)
        {
            printf("^");
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
    for (int i = 0; i < len; i++)
    {
        if (i == p1 || i == p2 || i == p3)
        {
            printf("|");
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
    return;
}

int binary_search(int *arr, int n, int x)
{
    int head = 0, tail = n - 1, mid;
    while (head <= tail) // tail -head >3 大区间二分，
    {
        mid = head + ((tail - head) >> 1);
        // mid = (head + tail) >> 1; ///
        output_binary_process(arr, n, head, tail, mid);
        if (arr[mid] == x)
            return mid;
        if (arr[mid] < x)
            head = mid + 1;
        else
            tail = mid - 1;
    }
    // for(int i = head; i <= tail; i++){//小区间顺序
    //     if(arr[i] == x) return i;
    // }
    return -1;
}

int binary_search01(int *arr, int n, int x)
{
    int head = 0, tail = n - 1, mid;
    while (head < tail)
    {
        mid = head + ((tail - head) >> 1);
        // mid = (head + tail) >> 1; ///
        output_binary_process(arr, n, head, tail, mid);
        if (arr[mid] < x)
            head = mid + 1;
        else
            tail = mid;
    }

    return head;
}

int *getRandData(int n)
{
    int *arr = (int *)malloc(sizeof(int) * n);
    arr[0] = rand() % 10;
    for (int i = 1; i < n; i++)
    {
        arr[i] = arr[i - 1] + rand() % 5 + 1;
    }
    return arr;
}

void output(int *arr, int n)
{
    int len = 0;
    for (int i = 0; i < n; i++)
    {
        len += printf("%5d", i);
    }
    printf("\n");
    for (int i = 0; i < len; i++)
        printf("-");
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%5d", arr[i]);
    }
    printf("\n");
    return;
}

int main()
{
    srand(time(0));
    int n, x;
    scanf("%d", &n);
    int *arr = getRandData(n);
    output(arr, n);
    while (~scanf("%d", &x))
    {
        printf("arr[%d] = %d \n", binary_search01(arr, n, x), x);
    }
    return 0;
}

//  x的平方根
int mySqrt(int x)
{
    double head = 0, tail = x, mid;
    tail += 1;
    for (int i = 0; i < 100; i++)
    {
        mid = head + ((tail - head) / 2.0);
        if (mid * mid <= x)
            head = mid;
        else
            tail = mid;
    }
    return floor(head);
}
// 一个排序数组，找target，返回索引，若不在，末尾追加，返回index
int searchInsert(vector<int> &nums, int target)
{
    int head = 0, tail = nums.size() - 1, mid;
    while (tail - head > 3)
    {
        mid = (head + tail) >> 1;
        if (nums[mid] >= target)
            tail = mid;
        else
            head = mid + 1;
    }
    for (int i = head; i <= tail; i++)
    {
        if (nums[i] >= target)
            return i;
    }
    // 不在二分search的区间
    return nums.size();
}

// nums=[2,7,11, 15] target = 9 [0,1] 2+7 可对下标排序
int binary_se(vector<int> &nums, vector<int> &ind, int head, int x)
{
    int tail = ind.size() - 1, mid;
    while (head <= tail)
    {
        mid = (head + tail) >> 1;
        if (nums[ind[mid]] == x)
            return mid;
        if (nums[ind[mid]] < x)
            head = mid + 1;
        else
            tail = mid - 1;
    }
    return -1;
}
vector<int> twoSum(vector<int> &nums, int target)
{
    vector<int> ind(nums.size());
    for (int i = 0; i < ind.size(); i++)
        ind[i] = i;
    sort(ind.begin(), ind.end(), [&](int i, int j)
         { return nums[i] < nums[j]; });
    vector<int> ret(2);
    for (int i = 0; i < ind.size(); i++)
    {
        int val = nums[ind[i]];
        int j = binary_se(nums, ind, i + 1, target - val);
        if (j == -1)
            continue;
        int a = ind[i];
        int b = ind[j];
        if (a > b)
            swap(a, b);
        ret[0] = a;
        ret[1] = b;
    }
    return ret;
}

// ele的第一个位置，最后一个位置  >= x    >x
int binary_se_01(vector<int> &nums, int x)
{
    int head = 0, tail = nums.size() - 1, mid;
    while (tail - head > 3)
    {
        mid = (head + tail) >> 1;
        if (nums[mid] >= x)
            tail = mid;
        else
            head = mid + 1;
    }
    for (int i = head; i <= tail; i++)
    {
        if (nums[i] >= x)
            return i;
    }
    return nums.size();
}
vector<int> searchRange(vector<int> &nums, int target)
{
    vector<int> ret(2);
    ret[0] = ret[1] = -1;
    ret[0] = binary_se_01(nums, target);
    if (ret[0] == nums.size() || nums[ret[0]] != target)
    {
        ret[0] = ret[1] = -1;
        return ret;
    }
    ret[1] = binary_se_01(nums, target + 1) - 1; //最后一个位置， 8--ind--- 要找的7的最后位置ind-1
    return ret;
}

int bs(vector<int> &nums, int x)
{
    int head = 0, tail = nums.size() - 1, mid;
    while (head <= tail)
    {
        mid = (head + tail) >> 1;
        if (nums[mid] == x)
            return mid;
        if (nums[mid] < x)
            return mid + 1;
        else
            tail = mid - 1;
    }
    return -1;
}

// arr target -- target 左右减为0 前缀和 两个 [0] = 0
int minOperations(vector<int> &nums, int x)
{
    vector<int> suml(nums.size() + 1);
    vector<int> sumr(nums.size() + 1);
    suml[0] = sumr[0] = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        suml[i + 1] = suml[i] + nums[i];
    }
    for (int i = nums.size() - 1; i >= 0; --i)
    {
        sumr[nums.size() - 1] = sumr[nums.size() - i - 1] + nums[i];
    }
    int ans = -1;
    for (int i = 0; i < suml.size(); i++)
    {
        int j = bs(sumr, x - suml[i]);
        if (j == -1)
            continue;
        if (i + j > nums.size())
            continue;
        if (ans == -1 || ans > i + j)
            ans = i + j;
    }
    return ans;
}

class pickInd
{
    int n;
    vector<int> sum;
    pickInd(vector<int> &w) : sum(w)
    {
        for (int i = 1; i < sum.size(); i++)
            sum[i] += sum[i - 1];
        n = sum[sum.size() - 1];
    }
    int pickIndex()
    {
        int x = rand() % n;
        int head = 0, tail = sum.size() - 1;
        while (head < tail)
        {
            int mid = (head + tail) >> 1;
            if (sum[mid] <= x)
                head = mid + 1;
            else
                tail = mid;
        }
        return head;
    }
};

// houses= [1,2,3], heaters=[2]  1   2-1  3-2 找第一个>=x的ind
int bs01(vector<int> &nums, int x)
{
    int head = 0, tail = nums.size() - 1, mid;
    while (head < tail)
    {
        mid = (head + tail) >> 1;
        if (nums[mid] >= x)
            tail = mid;
        else
            head = mid + 1;
    }
    return head;
}

int findRadius(vector<int> &houses, vector<int> &heaters)
{
    sort(heaters.begin(), heaters.end());
    int ans = 0;
    for (auto x : houses)
    {
        int j = bs01(heaters, x); // >=x first ind
        int a = abs(heaters[j] - x);
        int b = (j ? x - heaters[j - 1] : a + 1); // a+1 --- 当j<=0时，a+1能让b在min(a,b)中返回小的a
        ans = max(ans, min(a, b));
    }
    return ans;
}

bool search(vector<int> &nums, int target)
{
    if (nums[0] == target || nums[nums.size() - 1] == target)
        return true;
    int l = 0, r = nums.size() - 1, mid, head, tail;
    while (l < nums.size() && nums[l] == nums[0])
        ++l;
    while (r >= 0 && nums[r] == nums[0])
        --r;
    head = l, tail = r;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (nums[mid] == target)
            return true;
        if (nums[mid] <= nums[tail])
        {
            if (target <= nums[tail] && target > nums[mid])
                l = mid + 1;
            else
                r = mid - 1;
        }
        else
        {
            if (target < nums[mid] && target >= nums[head])
                r = mid - 1;
            else
                l = mid + 1;
        }
    }
    return false;
}

double findK(vector<int> &nums1, vector<int> &nums2, int i, int j, int k)
{
    if (i == nums1.size())
        return nums2[j + k - 1];
    if (j == nums2.size())
        return nums1[i + k - 1];
    if (k == 1)
        return (nums1[i] < nums2[j] ? nums2[j] : nums1[i]);
    int a = min(k / 2, (int)nums1.size() - 1);
    int b = min(k - a, (int)nums2.size() - 1);
    a = k - b;
    if (nums1[i + a - 1] <= nums2[j + b - 1])
    {
        return findK(nums1, nums2, i + a, j, k - a); //去b里找
    }
    return findK(nums1, nums2, i, j + b, k - b); // 去a
}

// 寻找两个正序数组的中位数 【1，3】 【2】  【1,2,3] 2
double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
{
    int n = nums1.size(), m = nums2.size(), mid = (m + n + 1) / 2;
    double a = findK(nums1, nums2, 0, 0, mid);
    if ((n + m) % 2 == 1)
        return a;
    double b = findK(nums1, nums2, 0, 0, mid + 1);
    return (a + b) / 2.0;
}