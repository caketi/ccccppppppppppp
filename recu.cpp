#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <unistd.h>
#include <time.h>
using namespace std;

// nums = {10, 9, 2, 5 , 3, 7, 101, 18}  --4  {2,3,7,101}
int lengthOfLIS(vector<int> &nums)
{
    vector<int> dp(nums.size());
    vector<int> res(nums.size());

    int ans = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        dp[i] = 1;
        for (int j = 0; j < i; j++)
        {
            if (nums[j] >= nums[i])
                continue;
            dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(dp[i], ans);
    }
    return ans;
}

int maxProfit(vector<int> &prices)
{
    int ans = 0;
    for (int i = 0; i < prices.size(); i++)
    {
        if (prices[i] > prices[i - 1])
            ans += prices[i] - prices[i - 1];
    }
    return ans;
}

int coinChange(vector<int> &coins, int amount)
{
    vector<int> dp(amount + 1);
    dp[0] = 0;
    for (int i = 1; i <= amount; i++)
        dp[i] = -1;
    for (int i = 1; i <= amount; i++)
    {
        for (auto x : coins)
        {
            if (i < x)
                continue;
            if (dp[i - x] == -1)
                continue;
            if (dp[i] == -1 || dp[i] > dp[i - x] + 1)
                dp[i] = dp[i - x] + 1;
        }
    }
    return dp[amount];
}

int maxProduct(vector<int> &nums)
{
    int ans = INT16_MIN, max_num = 1, min_num = 1;
    for (auto x : nums)
    {
        if (x < 0)
            swap(max_num, min_num); // 可能有负数，两极反转
        max_num = max(x * max_num, x);
        min_num = min(x * min_num, x);
        ans = max(ans, max_num);
    }
    return ans;
}

int rob(vector<int> &nums)
{
    int n = nums.size();
    vector<vector<int>> dp;
    for (int i = 0; i < n; i++)
        dp.push_back(vector<int>(2));
    dp[0][0] = 0, dp[0][1] = nums[0];
    for (int i = 1; i < n; i++)
    {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]); // dp[i][0]不偷第i家
        dp[i][1] = dp[i - 1][0] + nums[i];          // dp[i][1]偷第i家
    }
    return max(dp[n - 1][0], dp[n - 1][1]);
}

//  cost = [10, 15, 20] 15
int minCostClimbingStairs(vector<int> &cost)
{
    int n = cost.size();
    vector<int> dp(n + 1);
    cost.push_back(0);
    dp[0] = cost[0];
    dp[1] = cost[1];
    for (int i = 2; i <= n; i++)
        dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
    return dp[n];
}

int minCost(vector<vector<int>> &costs)
{
    int n = costs.size();
    vector<vector<int>> dp;
    for (int i = 0; i < 2; i++)
        dp.push_back(vector<int>(3));
    for (int i = 0; i < 3; i++)
        dp[0][i] = costs[0][i];
    for (int i = 1; i < n; i++)
    {
        int ind = i % 2;
        int pre_ind = !ind;
        dp[ind][0] = min(dp[pre_ind][1], dp[pre_ind][2]) + costs[i][0];
        dp[ind][1] = min(dp[pre_ind][0], dp[pre_ind][2]) + costs[i][1];
        dp[ind][2] = min(dp[pre_ind][0], dp[pre_ind][1]) + costs[i][2];
    }
    int ind = (n - 1) % 2;
    return min(dp[ind][0], min(dp[ind][1], dp[ind][2]));
}

// 我到哪里去版本
int minumTotal2(vector<vector<int>> &triangle)
{
    int n = triangle.size();
    vector<vector<int>> dp;
    for (int i = 0; i < n; i++)
        dp.push_back(vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            dp[i][j] = INT16_MAX;
        }
    }
    dp[0][0] = triangle[0][0];
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + triangle[i + 1][j]);
            dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + triangle[i + 1][j + 1]);
        }
    }
    int ans = INT16_MAX;
    for (auto x : dp[n - 1])
        ans = min(ans, x);
    return ans;
}

// 最长公共子序列
int lonshare()
{
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size(), m = s2.size();
    int dp[n + 1][m + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}

// 我从哪里来版本
int miniumTotal(vector<vector<int>> &triangle)
{
    int n = triangle.size();
    vector<vector<int>> dp;
    for (int i = 0; i < 2; i++)
        dp.push_back(vector<int>(n));
    for (int i = 0; i < n; i++)
        dp[(n - 1) % 2][i] = triangle[n - 1][i];
    for (int i = n - 2; i >= 0; --i)
    {
        int ind = i % 2;
        int next_ind = !ind;
        for (int j = 0; j <= i; j++)
        {
            dp[ind][j] = min(dp[next_ind][j], dp[next_ind][j + 1]) + triangle[i][j];
        }
    }
    return dp[0][0];
}

vector<int> getRow(int rowIndex)
{
    int n = rowIndex;
    vector<vector<int>> f;
    for (int i = 0; i < 2; i++)
        f.push_back(vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        int ind = i % 2;
        int pre_ind = !ind;
        for (int j = 1; j <= i; j++)
        {
            f[ind][j] = f[pre_ind][j] + f[pre_ind][j - 1];
        }
    }
    return f[(n - 1) % 2];
}

int maxSubArray(vector<int> &nums)
{
    for (int i = 1; i < nums.size(); i++)
        nums[i] += nums[i - 1];
    int pre = 0, ans = INT32_MIN;
    for (auto x : nums)
    {
        ans = max(x - pre, ans);
        pre = min(x, pre);
    }
    return ans;
}

int main()
{
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << lengthOfLIS(nums) << endl;

    // vector<vector<int>> costs = {{17, 2, 17}, {16, 16, 5}, {14, 3, 19}};
    // cout << minCost(costs) << endl;
}