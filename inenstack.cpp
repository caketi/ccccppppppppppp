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
#include <unordered_set>
#include <assert.h>
#include <time.h>
#include <math.h>
using namespace std;

string samllestSubsequence(string s){
    string ret;
    unordered_map<char, int> cnt;
    for(auto x : s) cnt[x] +=1;
    unordered_set<char> h;
    for(auto x : s){
        if( h.find(x) == h.end() ){
            while(ret.size() && cnt[ret.back()] && ret.back()>x){
                h.erase(h.find(ret.back()));
                ret.pop_back();
            }
            h.insert(x);
            ret.push_back(x);
        }
        cnt[x] -= 1;
    }
    return ret;
}
string removeKdigits(string num, int k){
    // to make rest as small as possible
    if(k >= num.size()) return "0";
    string ret;
    for(auto x :num){
        while( k && ret.size() && ret.back() > k) ret.pop_back(), k-=1;
        ret.push_back(x);
    }
    if(k != 0) ret = ret.substr(0, ret.size() - k); // 有剩余，t了
    int ind = 0;
    while(ret[ind] == '0') ++ind; //去掉0 要求不能有前导0
    ret = ret.substr(ind, ret.size());
    if(ret == "") ret = "0";
    return ret;
}

int trap(vector<int> &height)
{
    int ans = 0;
    stack<int> s;
    for(int i = 0; i<height.size(); i++){
        while(s.size() && height[i] > height[s.top()]){
            int now =s.top();
            s.pop();
            if(s.size() == 0) continue;
            int a = height[i] - height[now];
            int b  = height[s.top()] - height[now];
            ans += (i-s.top() -1) * min(a,b);
        }
        s.push(i);
    }
    return ans;
}
// 132模式 大哥 三哥 二哥
class fidn132
{
    bool find132pattern(vector<int> &nums)
    {
        vector<int> l(nums.size());
        l[0] = INT32_MAX;
        for (int i = 1; i < nums.size(); i++)
            l[i] = min(l[i - 1], nums[i - 1]);
        stack<int> s;
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            int val = nums[i];
            while (s.size() && nums[i] > s.top())
                val = s.top(), s.pop();
            s.push(nums[i]);
            if (l[i] < nums[i] && val < nums[i] && val > l[i])
                return true;
        }
        return false;
    }
};
class nextGreaterele
{
    // nums1 = [4,1,2] nums2 = [1,3,4,2] nums1s是nums2的子集 [-1,3,-1]
    vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_map<int, int> h;
        stack<int> s;
        for (auto x : nums2)
        {
            while (s.size() && x > s.top())
            {
                h[s.top()] = x;
                s.pop();
            }
            s.push(x);
        }
        vector<int> ret(nums1.size());
        for (int i = 0; i < nums1.size(); i++)
        {
            if (h.find(nums1[i]) == h.end())
                ret[i] = -1;
            else
                ret[i] = h[nums1[i]];
        }
        return ret;
    }
};

class sumSubarraymins
{
    int sumSubarrayMins(vector<int> &arr)
    {
        stack<int> s;
        int mod_num = 1e9 + 7;
        long long ans = 0;
        vector<long long> sum(arr.size() + 1);
        sum[0] = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            while (s.size() && arr[i] <= arr[s.top()])
                s.pop();
            int ind = s.size() ? s.top() : -1;
            s.push(i);
            sum[s.size()] = (sum[s.size() - 1] + arr[i] * (i - ind)) % mod_num;
            ans += sum[s.size()];
            ans %= mod_num;
        }
        return ans;
    }
};

class maxSumMinpro
{
    int maxSumMinProduct(vector<int> &nums)
    {
        stack<int> s;
        vector<int> l(nums.size()), r(nums.size());
        int n = nums.size();
        for (int i = 0; i < n; i++)
            l[i] = -1, r[i] = n;
        for (int i = 0; i < n; i++)
        {
            while (s.size() && nums[i] <= nums[s.top()])
            {
                r[s.top()] = i;
                s.pop();
            }
            if (s.size())
                l[i] = s.top();
            s.push(i);
        }
        vector<int> sum(n + 1);
        sum[0] = 0;
        for (int i = 0; i < n; i++)
            sum[i + 1] = sum[i] + nums[i];
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans = max(ans, nums[i] * (sum[r[i]] - sum[l[i] + 1]));
        }
        return ans;
    }
};

class largestArea
{
    int largestRectangleArea(vector<int> &heights)
    {
        stack<int> s;
        vector<int> l(heights.size()), r(heights.size());
        int n = heights.size();
        for (int i = 0; i < n; i++)
            l[i] = -1, r[i] = n;
        for (int i = 0; i < n; i++)
        {
            while (s.size() && heights[i] <= heights[s.top()])
            {
                r[s.top()] = i;
                s.pop();
            }
            if (s.size())
                l[i] = s.top();
            s.push(i);
        }
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans = max(ans, heights[i] * (r[i] - l[i] - 1));
        }
        return ans;
    }
};

class DailyTem
{
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        vector<int> ret;
        stack<int> s;
        for (int i = 0; i < temperatures.size(); i++)
        {
            while (s.size() && temperatures[i] > temperatures[s.top()])
            {
                ret[s.top()] = i - s.top();
                s.pop();
            }
            s.push(i);
        }
        return ret;
    }
};

class StockSpanner
{
    typedef pair<int, int> PII;
    int t;
    stack<PII> s;
    StockSpanner()
    {
        s.push(PII(INT32_MAX, t++));
    }
    int next(int price)
    {
        while (s.size() && price >= s.top().first)
            s.pop();
        int ret = t - s.top().second;
        s.push(PII(price, t++));
        return ret;
    }
};

void output(vector<int> &arr, const char *msg)
{
    printf("%s", msg);
    for (auto x : arr)
    {
        printf("%5d", x);
    }
    printf("\n");
}
int main()
{ //维护前后比我小
    int n;

    cin >> n;
    vector<int> arr(n);
    vector<int> pre(n), nex(n);
    stack<int> s;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        while (s.size() && arr[i] < arr[s.top()])
        {
            for (auto x : arr)
                cout << x;
            nex[s.top()] = i;

            s.pop();
        }
        if (s.size() == 0)
            pre[i] = -1;
        else
            pre[i] = s.top();
        s.push(i);
    }
    while (s.size())
        nex[s.top()] = n, s.pop();
    output(arr, "now: ");
    output(pre, "pre: ");
    output(nex, "nex: ");
    return 0;
}

class nextGreater
{
    vector<int> nextGreaterElements(vector<int> &nums)
    {
        stack<int> s;
        vector<int> ret(nums.size());
        for (int i = 0; i < nums.size(); i++)
            ret[i] = -1;
        for (int i = 0; i < nums.size(); i++)
        {
            while (s.size() && nums[i] > nums[s.top()])
            {
                ret[s.top()] = nums[i];
                s.pop();
            }
            s.push(i);
        }
        for (int i = 0; i < nums.size(); i++)
        {
            while (s.size() && nums[i] > nums[s.top()])
            {
                ret[s.top()] = nums[i];
                s.pop();
            }
            s.push(i);
        }
        return ret;
    }
};

class MinStack
{
public:
    stack<int> s, min_s;
    MinStack() {}
    void push(int val)
    {
        s.push(val);
        if (min_s.size() == 0 || val <= min_s.top())
        {
            min_s.push(val);
        }
        return;
    }
    void pop()
    {
        if (s.top() == min_s.top())
            min_s.pop();
        s.pop();
        return;
    }
    int top()
    {
        return s.top();
    }
    int getMin()
    {
        return min_s.top();
    }
};