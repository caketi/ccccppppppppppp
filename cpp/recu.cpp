#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include <time.h>
using namespace std;
int calculateMinimumHP(vector<vector<int>> & dungeon){
    if(dungeon.size() == 0){
        return 0;
    }
    vector<vector<int>> dp(dungeon.size(), vector<int>(dungeon[0].size(), 0));
    int row = dungeon.size();
    int column = dungeon[0].size();
    dp[row-1][column-1] = max(1, 1-dungeon[row-1][column-1]);
    for(int i = column -2; i >= 0; i--){
        dp[row-1][i] = max(1, dp[row-1][i+1] - dungeon[row-1][i]);
    }
    for(int i = row -2; i >= 0; i--){
        dp[i][column -1] = max(1, dp[i+1][column -1] - dungeon[i][column-1]);
    }
    for(int i = row-2; i >= 0; i--){
        for(int j = column -2; j>=0; j--){
            int dp_min = min(dp[i+1][j], dp[i][j+1]);
            dp[i][j] = max(1, dp_min-dungeon[i][j]);
        }
    }
    return dp[0][0];
}

int minPathSum(vector<vector<int>> &grid) {
  if (grid.size() == 0) {
    return 0;
  }
  int row = grid.size();
  int column = grid[0].size();
  vector<vector<int>> dp(row, vector<int>(column, 0));
  dp[0][0] = grid[0][0];
  for (int i = 1; i < column; i++) {
    dp[0][i] = dp[0][i - 1] + grid[0][i];
  }
  for (int i = 1; i < row; i++) {
    dp[i][0] = dp[i - 1][0] + grid[i][0];
    for (int j = 1; j < column; j++) {
      dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
    }
  }
  return dp[row - 1][column - 1];
}
// pair -- 元素和count绑定
void merge_sort_two_vec(vector<pair<int, int>> &sub_vec1,
                        vector<pair<int, int>> &sub_vec2,
                        vector<pair<int, int>> &vec, vector<int> &count) {
  int i = 0;
  int j = 0;
  while (i < sub_vec1.size() && j < sub_vec2.size()) {
    if (sub_vec1[i].first <= sub_vec2[j].first) {
      count[sub_vec1[i].second] += j;
      vec.push_back(sub_vec1[i]);
      i++;
    } // 插入i指针指向的元素时，对应的count[i]---j的索引值 即明确比  a[i] > a[j]
      // j++ ====  a[i] < a[j] 那么我比之前都大
    else {
      vec.push_back(sub_vec2[j]);
      j++;
    }
  }
  for (; i < sub_vec1.size(); i++) {
    count[sub_vec1[i].second] += j;
    vec.push_back(sub_vec1[i]);
  }
  for (; j < sub_vec2.size(); j++) {
    vec.push_back(sub_vec2[j]);
  }
}
void merge_sort(vector<pair<int, int>> &vec, vector<int> &count) {
  if (vec.size() < 2) {
    return;
  }
  int mid = vec.size() / 2;
  vector<pair<int, int>> sub_vec1;
  vector<pair<int, int>> sub_vec2;
  for (int i = 0; i < mid; i++) {
    sub_vec1.push_back(vec[i]);
  }
  for (int i = mid; i < vec.size(); i++) {
    sub_vec2.push_back(vec[i]);
  }
  merge_sort(sub_vec1, count);
  merge_sort(sub_vec2, count);
  vec.clear();
  merge_sort_two_vec(sub_vec1, sub_vec2, vec, count);
}

vector<int> countSmaller(vector<int> &nums) {
  vector<pair<int, int>> vec;
  vector<int> count;
  for (int i = 0; i < nums.size(); i++) {
    vec.push_back(make_pair(nums[i], i));
    count.push_back(0);
  }
  merge_sort(vec, count);
  return count;
}

// N皇后
void put_down_the_queen(int x, int y, vector<vector<int>> &mark) {
  static const int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1}; // 八方旅人
  static const int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
  mark[x][y] = 1;                         // (x,y)放皇后
  for (int i = 1; i < mark.size(); i++) { // 哪一行，压缩饼干，二向箔打击
    for (int j = 0; j < 8; j++) {
      int new_x = x + i * dx[j];
      int new_y = y + i * dy[j];
      if (new_x >= 0 && new_x < mark.size() && new_y >= 0 &&
          new_y < mark.size()) {
        mark[new_x][new_y] = 1;
      }
    }
  }
}
void generate_queen(int k, int n, vector<string> &location,
                    vector<vector<string>> &result,
                    vector<vector<int>> &mark) { // k-放了几个皇后
  if (k == n) {
    result.push_back(location);
    return;
  }
  for (int i = 0; i < n; i++) {
    if (mark[k][i] == 0) {
      vector<vector<int>> tmp_mark = mark; // 记录回溯前的mark
      location[k][i] = 'Q';                // 记录当前皇后位置
      put_down_the_queen(k, i, mark);
      generate_queen(k + 1, n, location, result, mark);
      mark = tmp_mark;      // 回溯
      location[k][i] = '.'; // 回溯
    }
  }
}

vector<vector<string>> solveNQueens(int n) {
  vector<vector<string>> result;
  vector<vector<int>> mark; // 标记是否可以放
  vector<string> location;  // 记录皇后的位置
  for (int i = 0; i < n; i++) {
    mark.push_back((vector<int>()));
    for (int j = 0; j < n; j++) {
      mark[i].push_back(0);
    }
    location.push_back("");
    location[i].append(n, '.');
  }
  generate_queen(0, n, location, result, mark);
  return result;
}
void generate_string_item(
    string item, int left, int right,
    vector<string>
        &result) { // left,right ---
                   // 可以放括号的剩余数量，海克斯最后通牒，精准，优雅
  if (left == 0 && right == 0) {
    result.push_back(item);
    return;
  }
  if (left > 0) {
    generate_string_item(item + '(', left - 1, right, result);
  }
  if (left > right) {
    generate_string_item(item + ')', left, right - 1, result);
  }
}
vector<string> generate_parenthesis(int n) {
  vector<string> result;
  generate_string_item("", n, n, result);
  return result;
}

// n---括号组数
void generate_parenthesis_may_illegal(string item, int n,
                                      vector<string> &result) {
  if (item.size() == 2 * n) {
    result.push_back(item);
    return;
  }
  generate_parenthesis_may_illegal(item + '(', n, result);
  generate_parenthesis_may_illegal(item + ')', n, result);
}

void generateSum(int i, vector<int> &nums, vector<vector<int>> &result,
                 vector<int> &item, set<vector<int>> &res_set, int sum,
                 int target) {
  if (i >= nums.size() || sum > target) {
    return;
  }
  sum += nums[i]; // 看这里，选不选
  item.push_back(nums[i]);

  if (target == sum && res_set.find(item) == res_set.end()) {
    result.push_back(item);
    res_set.insert(item);
  }
  generateSum(i + 1, nums, result, item, res_set, sum, target);

  sum -= nums[i]; // 看这里，选不选
  item.pop_back();
  generateSum(i + 1, nums, result, item, res_set, sum, target);
}
vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
  vector<vector<int>> result;
  vector<int> item;
  set<vector<int>> res_set;
  sort(candidates.begin(), candidates.end());
  generateSum(0, candidates, result, item, res_set, 0, target);
  return result;
}

void generate_no_dup(int i, vector<int> &nums, vector<vector<int>> &result,
                     vector<int> &item, set<vector<int>> &res_set) {
  if (i >= nums.size()) {
    return;
  }
  item.push_back(nums[i]);
  if (res_set.find(item) == res_set.end()) // 去重
  {
    result.push_back(item);
    res_set.insert(item);
  }
  generate_no_dup(i + 1, nums, result, item, res_set);
  item.pop_back();
  generate_no_dup(i + 1, nums, result, item, res_set);
}
vector<vector<int>> subsets_with_dup(vector<int> &nums) {
  vector<vector<int>> result;
  vector<int> item;
  set<vector<int>> res_set;
  sort(nums.begin(), nums.end());
  result.push_back(item);
  generate_no_dup(0, nums, result, item, res_set);
  return result;
}

vector<vector<int>> subsets_bitop(vector<int> &nums) {
  vector<vector<int>> result;
  int all_set = 1 << nums.size();
  for (int i = 0; i < all_set; i++) {
    vector<int> item;
    for (int j = 0; j < nums.size(); j++) {
      if (i & (1 << j)) {
        item.push_back(nums[j]);
      }
    }
    result.push_back(item);
  }
  return result;
}
void generate(int i, vector<int> &nums, vector<int> &item,
              vector<vector<int>> &result) {
  if (i >= nums.size()) {
    return;
  }
  item.push_back(nums[i]);
  result.push_back(item);
  generate(i + 1, nums, item, result); // 选择 不选
  item.pop_back();
  generate(i + 1, nums, item, result);
}
vector<vector<int>> subsets(vector<int> &nums) {
  vector<vector<int>> result;
  vector<int> item;       // 回溯时，产生各个子集的数组
  result.push_back(item); // 空集push-result
  generate(0, nums, item, result);
  return result;
}

// nums = {10, 9, 2, 5 , 3, 7, 101, 18}  --4  {2,3,7,101}
int lengthOfLIS(vector<int> &nums) {
  vector<int> dp(nums.size());
  vector<int> res(nums.size());

  int ans = 0;
  for (int i = 0; i < nums.size(); i++) {
    dp[i] = 1;
    for (int j = 0; j < i; j++) {
      if (nums[j] >= nums[i])
        continue;
      dp[i] = max(dp[i], dp[j] + 1);
    }
    ans = max(dp[i], ans);
  }
  return ans;
}
int lengthOfLISV2(vector<int> &nums) {
  if (nums.size() == 0) {
    return 0;
  }
  vector<int> dp(nums.size(), 0);
  dp[0] = 1;
  int LIS = 1;
  for (int i = 1; i < dp.size(); i++) {
    dp[i] = 1;
    for (int j = 0; j < i; j++) {
      if (nums[i] > nums[j] && dp[i] < dp[j] + 1) {
        dp[i] = dp[j] + 1;
      }
    }
    if (LIS < dp[i]) {
      LIS = dp[i];
    }
  }
  return LIS;
}
int lengthOfLISV3(vector<int> &nums) {
  if (nums.size() == 0) {
    return 0;
  }
  vector<int> stack;
  stack.push_back(nums[0]);
  for (int i = 1; i < nums.size(); i++) {
    if (nums[i] > stack.back()) {
      stack.push_back(nums[i]);
    } else {
      for (int j = 0; j < stack.size(); j++) {
        if (stack[j] >= nums[i]) {
          stack[j] = nums[i];
          break;
        }
      }
    }
  }
  return stack.size();
}
int maxProfit(vector<int> &prices) {
  int ans = 0;
  for (int i = 0; i < prices.size(); i++) {
    if (prices[i] > prices[i - 1])
      ans += prices[i] - prices[i - 1];
  }
  return ans;
}

int coinChange(vector<int> &coins, int amount) {
  vector<int> dp(amount + 1);
  dp[0] = 0;
  for (int i = 1; i <= amount; i++)
    dp[i] = -1;
  for (int i = 1; i <= amount; i++) {
    for (auto x : coins) {
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
// i--金额 coins[j] ---第j个面值的金额
int coinChangeV2(vector<int> &coins, int amount) {
  vector<int> dp;
  for (int i = 0; i <= amount; i++) {
    dp.push_back(-1);
  }
  dp[0] = 0;
  for (int i = 1; i <= amount; i++) {
    for (int j = 0; j < coins.size(); j++) {
      if (i - coins[j] >= 0 && dp[i - coins[j]] != -1) {
        if (dp[i] == -1 || dp[i] > dp[i - coins[j]] + 1) {
          dp[i] = dp[i - coins[j]] + 1;
        }
      }
    }
  }
  return dp[amount];
}
int maxProduct(vector<int> &nums) {
  int ans = INT16_MIN, max_num = 1, min_num = 1;
  for (auto x : nums) {
    if (x < 0)
      swap(max_num, min_num); // 可能有负数，两极反转
    max_num = max(x * max_num, x);
    min_num = min(x * min_num, x);
    ans = max(ans, max_num);
  }
  return ans;
}
// 前i个房间能获得的最大财宝 选择第i个房间：dp[i-2] + nums[i] 不选 dp[i-1] (i>=3)
int rob(vector<int> &nums) {
  int n = nums.size();
  vector<vector<int>> dp;
  for (int i = 0; i < n; i++)
    dp.push_back(vector<int>(2));
  dp[0][0] = 0, dp[0][1] = nums[0];
  for (int i = 1; i < n; i++) {
    dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]); // dp[i][0]不偷第i家
    dp[i][1] = dp[i - 1][0] + nums[i];          // dp[i][1]偷第i家
  }
  return max(dp[n - 1][0], dp[n - 1][1]);
}
int robV2(vector<int> &nums) {
  if (nums.size() == 0) {
    return 0;
  }
  if (nums.size() == 1) {
    return nums[0];
  }
  vector<int> dp(nums.size(), 0);
  dp[0] = nums[0];
  dp[1] = max(nums[0], nums[1]);
  for (int i = 2; i < nums.size(); i++) {
    dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
  }
  return dp[nums.size() - 1];
}
int climbStairs(int n) {
  if (n == 1 || n == 2) {
    return n;
  }
  return climbStairs(n - 1) + climbStairs(n - 2);
}
int clibmStairsV2(int n) {
  vector<int> dp(n + 3, 0);
  dp[1] = 1;
  dp[2] = 2;
  for (int i = 3; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n];
}

//  cost = [10, 15, 20] 15
int minCostClimbingStairs(vector<int> &cost) {
  int n = cost.size();
  vector<int> dp(n + 1);
  cost.push_back(0);
  dp[0] = cost[0];
  dp[1] = cost[1];
  for (int i = 2; i <= n; i++)
    dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
  return dp[n];
}

int minCost(vector<vector<int>> &costs) {
  int n = costs.size();
  vector<vector<int>> dp;
  for (int i = 0; i < 2; i++)
    dp.push_back(vector<int>(3));
  for (int i = 0; i < 3; i++)
    dp[0][i] = costs[0][i];
  for (int i = 1; i < n; i++) {
    int ind = i % 2;
    int pre_ind = !ind;
    dp[ind][0] = min(dp[pre_ind][1], dp[pre_ind][2]) + costs[i][0];
    dp[ind][1] = min(dp[pre_ind][0], dp[pre_ind][2]) + costs[i][1];
    dp[ind][2] = min(dp[pre_ind][0], dp[pre_ind][1]) + costs[i][2];
  }
  int ind = (n - 1) % 2;
  return min(dp[ind][0], min(dp[ind][1], dp[ind][2]));
}
// 从数字三角形顶端到底端各数字和最小的路径之和，每次可向下走相邻的两个位置
int mininumTotal(vector<vector<int>> &triangle) {
  if (triangle.size() == 0) {
    return 0;
  }
  vector<vector<int>> dp;
  for (int i = 0; i < triangle.size(); i++) {
    dp.push_back(vector<int>());
    for (int j = 0; j < triangle.size(); j++) {
      dp[i].push_back(0);
    }
  }
  for (int i = 0; i < dp.size(); i++) {
    dp[dp.size() - 1][i] = triangle[dp.size() - 1][i];
  }
  for (int i = dp.size() - 2; i >= 0; i--) {
    for (int j = 0; j < dp[i].size(); j++) {
      dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + triangle[i][j];
    }
  }
  return dp[0][0];
}
// 我到哪里去版本
int minumTotal2(vector<vector<int>> &triangle) {
  int n = triangle.size();
  vector<vector<int>> dp;
  for (int i = 0; i < n; i++)
    dp.push_back(vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      dp[i][j] = INT16_MAX;
    }
  }
  dp[0][0] = triangle[0][0];
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j <= i; j++) {
      dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + triangle[i + 1][j]);
      dp[i + 1][j + 1] =
          min(dp[i + 1][j + 1], dp[i][j] + triangle[i + 1][j + 1]);
    }
  }
  int ans = INT16_MAX;
  for (auto x : dp[n - 1])
    ans = min(ans, x);
  return ans;
}

// 最长公共子序列
int lonshare() {
  string s1, s2;
  cin >> s1 >> s2;
  int n = s1.size(), m = s2.size();
  int dp[n + 1][m + 1];
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
      }
    }
  }
  cout << dp[n][m] << endl;
  return 0;
}

// 我从哪里来版本
int miniumTotal(vector<vector<int>> &triangle) {
  int n = triangle.size();
  vector<vector<int>> dp;
  for (int i = 0; i < 2; i++)
    dp.push_back(vector<int>(n));
  for (int i = 0; i < n; i++)
    dp[(n - 1) % 2][i] = triangle[n - 1][i];
  for (int i = n - 2; i >= 0; --i) {
    int ind = i % 2;
    int next_ind = !ind;
    for (int j = 0; j <= i; j++) {
      dp[ind][j] = min(dp[next_ind][j], dp[next_ind][j + 1]) + triangle[i][j];
    }
  }
  return dp[0][0];
}

vector<int> getRow(int rowIndex) {
  int n = rowIndex;
  vector<vector<int>> f;
  for (int i = 0; i < 2; i++)
    f.push_back(vector<int>(n));
  for (int i = 0; i < n; i++) {
    int ind = i % 2;
    int pre_ind = !ind;
    for (int j = 1; j <= i; j++) {
      f[ind][j] = f[pre_ind][j] + f[pre_ind][j - 1];
    }
  }
  return f[(n - 1) % 2];
}

int maxSubArray(vector<int> &nums) {
  for (int i = 1; i < nums.size(); i++)
    nums[i] += nums[i - 1];
  int pre = 0, ans = INT32_MIN;
  for (auto x : nums) {
    ans = max(x - pre, ans);
    pre = min(x, pre);
  }
  return ans;
}

bool is_palindrome(string &s, int i, int j) {
  while (i <= j) {
    if (s[i] - s[j])
      return false;
    ++i, --j;
  }
  return true;
}

int main() {
  string s;
  cin >> s;
  int n = s.size();
  vector<int> dp(n + 1);
  dp[0] = 0; // dp[i]===字符串长度i
  for (int i = 1; i <= n; i++) {
    dp[i] = i;
    for (int j = 0; j < i; j++) {
      if (is_palindrome(s, j, i - 1)) {
        dp[i] = min(dp[j] + 1, dp[i]);
      }
    }
  }
  cout << dp[n] << endl;
  return 0;

  // vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
  // cout << lengthOfLIS(nums) << endl;

  // vector<vector<int>> costs = {{17, 2, 17}, {16, 16, 5}, {14, 3, 19}};
  // cout << minCost(costs) << endl;
}