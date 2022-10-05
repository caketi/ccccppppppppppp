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
#include <time.h>
using namespace std;

// #define MAX_N 100
#define MAX_V 10000
// int v[MAX_N + 5], w[MAX_N + 5]; //去掉，一边读入
// int dp[MAX_N + 5][MAX_V + 5] = {0};
int dp[2][MAX_V + 5] = {0};

int main()
{
    int V, n, v, w;
    cin >> V >> n; // V-最大承重， n-物品数
    for (int i = 1; i <= n; i++)
    {
        cin >> v >> w; // v-zhong , w-jia
    }
    for (int i = 1; i <= n; i++)
    {
        int ind = i % 2;
        int pre_ind = !ind; //滚动数组

        for (int j = 0; j <= V; j++)
        {
            dp[ind][j] = dp[pre_ind][j];
            if (j >= v) //背包容量够
                dp[ind][j] = max(dp[ind][j], dp[pre_ind][j - v] + w);
        }
    }
    cout << dp[n % 2][V] << endl;
    return 0;
}

int maxProfit(vector<int> &prices, int fee)
{
    int n = prices.size();
    int dp[n][2];
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for (int i = 1; i < n; i++)
    {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
    }
    return max(dp[n - 1][0], dp[n - 1][1]);
}

int rob2(vector<int> &nums)
{ //环拆成非环，相邻不偷

    int n = nums.size();
    if (n == 1)
        return nums[0];
    int dp[n][2];
    dp[0][0] = 0;
    dp[0][1] = nums[0];
    for (int i = 1; i < n; i++)
    {
        dp[i][0] = max(dp[i - 1][1], dp[i - 1][0]);
        dp[i][1] = dp[i - 1][0] + nums[i];
    }
    int ans1 = dp[n - 1][0]; //不偷最后一个
    dp[0][0] = 0;
    dp[0][1] = 0; // 不偷第一个
    for (int i = 1; i < n; i++)
    {
        dp[i][0] = max(dp[i - 1][1], dp[i - 1][0]);
        dp[i][1] = dp[i - 1][0] + nums[i];
    }
    int ans2 = max(dp[n - 1][0], dp[n - 1][1]);
    return max(ans1, ans2);
}

bool canPartition(vector<int> &nums)
{
    int sum = 0;
    for (auto x : nums)
        sum += x;
    if (sum % 2)
        return false;
    int f[sum + 1];
    f[0] = 1;
    sum = 0;
    for (auto x : nums)
    {
        sum += x;
        for (int j = sum; j >= x; j--)
        {
            f[j] |= f[j - x];
        }
    }
    return f[sum / 2];
}
// strs = {"10", "0001", "111001", "1", "0"} m = 5, n =3 =--- 4
// 最多5个0,3个1的最大子集
int findMaxForm(vector<string> &strs, int m, int n)
{
    int dp[m + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    for (auto x : strs)
    {
        int cnt0 = 0, cnt1 = 0;
        for (auto y : x)
        {
            if (y == '0')
                cnt0 += 1;
            else
                cnt1 += 1;
        }
        for (int i = m; i >= cnt0; --i)
        {
            for (int j = n; j >= cnt1; --j)
            {
                dp[i][j] = max(dp[i][j], dp[i - cnt0][j - cnt1] + 1);
            }
        }
    }
    return dp[m][n];
}
// nums = {1,1,1,1,1} target = 3 output= 5 方法让目标和为3， 可自由加减
int findTargetSumWays(vector<int> &nums, int target)
{
    int n = nums.size(), sum = 0;
    for (auto x : nums)
        sum += x;
    int buff[2][2 * sum + 5], *f[2] = {buff[0] + sum + 2, buff[1] + sum + 2}; // buff偏移数组，-x====+x 开辟2x+1中间p来偏移
    sum = 0;
    memset(buff, 0, sizeof(buff));
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        int ind = i % 2;
        int pre_ind = !ind;
        int x = nums[i - 1];
        memset(buff[ind], 0, sizeof(buff[ind]));
        for (int j = -sum; j <= sum; j++)
        {
            f[ind][j + x] += f[pre_ind][j];
            f[ind][j - x] += f[pre_ind][j];
        }
        sum += x;
    }
    return f[n % 2][target];
}

// coins = {1,2,5} amount = 11   = 5 + 5 + 1   output=3
int coinChange(vector<int> &coins, int amount)
{
    int dp[amount + 1];
    for (int i = 0; i <= amount; i++)
        dp[i] = -1;
    dp[0] = 0;
    for (auto x : coins)
    {
        for (int j = x; j <= amount; j++)
        {
            if (dp[j - x] == -1)
                continue;
            if (dp[j] == -1 || dp[j] > dp[j - x] + 1)
                dp[j] = dp[j - x] + 1;
        }
    }
    return dp[amount];
}
// nums={1,2,3} ,target = 4  output = 7所有可能的组合
int combinationSum4(vector<int> &nums, int target)
{
    unsigned int f[target + 1];
    memset(f, 0, sizeof(f));
    f[0] = 1;
    for (int i = 1; i <= target; i++)
    {
        for (auto x : nums)
        {
            if (i < x)
                continue;
            f[i] += f[i - x];
        }
    }
    return f[target];
}
// 462. {1,2,3}-- output--2最小移动2步每个数相等
int minMoves2(vector<int> &nums)
{
    int n = nums.size();
    nth_element(nums.begin(), nums.begin() + n / 2, nums.end());
    int x0 = nums[n / 2], ans = 0;
    for (auto x : nums)
        ans += abs(x - x0);
    return ans;
}

// 77. n=4, k=2 output=[1,n] 所有可能的k个数的组合
void dfs(int i, int n, int cnt, int k, vector<int> &buff, vector<vector<int>> &ret)
{
    if (cnt == k)
    {
        ret.push_back(buff);
        return;
    }
    if (n - i + 1 < k - cnt)
        return;
    buff[cnt] = i;
    dfs(i + 1, n, cnt + 1, k, buff, ret);
    dfs(i + 1, n, cnt, k, buff, ret);
    return;
}
vector<vector<int>> combine(int n, int k)
{
    vector<int> buff(k);
    vector<vector<int>> ret;
    dfs(1, n, 0, k, buff, ret);
    return ret;
}

