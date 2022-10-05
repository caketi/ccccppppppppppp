#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <stdint.h>
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

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
struct Data
{
    Data(TreeNode *node, TreeNode *father, int deepth = 0) : node(node), deepth(deepth), father(father) {}
    TreeNode *node, *father;
    int deepth;
};

int dfs(TreeNode *root, int x, TreeNode *&father)
{
    if (root == nullptr)
        return -1;
    if (root->val == x)
        return 0;
    int l;
    father = root;
    l = dfs(root->left, x, father);
    if (l != -1)
        return l + 1;
    l = dfs(root->right, x, father);
    if (l != -1)
        return l + 1;
    return -1;
}
// 不同父亲，同层
bool isCousins(TreeNode *root, int x, int y)
{
    int d1, d2;
    TreeNode *father_x = nullptr, *father_y = nullptr;
    d1 = dfs(root, x, father_x);
    d2 = dfs(root, y, father_y);
    return d1 == d2 && father_x != father_y;
}

bool isCousinsbfs(TreeNode *root, int x, int y)
{
    int d1, d2;
    TreeNode *father_x = nullptr, *father_y = nullptr;
    queue<Data> q;
    q.push(Data(root, 0));
    while (!q.empty())
    {
        Data cur = q.front();
        if (cur.node->val == x)
            d1 = cur.deepth, father_x = cur.father;
        if (cur.node->val == y)
            d2 = cur.deepth, father_y = cur.father;
        if (cur.node->left)
        {
            q.push(Data(cur.node->left, cur.node, cur.deepth + 1));
        }
        if (cur.node->right)
        {
            q.push(Data(cur.node->right, cur.node, cur.deepth + 1));
        }
        q.pop();
    }
    return d1 == d2 && father_x != father_y;
}

struct Dat
{
    int i, j, k; // ij位置 k--位置到0的距离
    Dat(int i = 0, int j = 0, int k = 0) : i(i), j(j), k(k) {}
};
void init_queue(queue<Dat> &q, vector<vector<int>> &vis, int n, int m, vector<vector<int>> &mat)
{
    for (int i = 0; i < n; i++)
    {
        vis.push_back(vector<int>());
        for (int j = 0; j < m; j++)
        {
            vis[i].push_back(-1);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j])
                continue; // 不加入1， 加入所有0位置
            vis[i][j] = 0;
            q.push(Dat(i, j, 0));
        }
    }
    return;
}
int dir1[4][2] = {0, 1, 1, 0, 0, -1, -1, 0}; // 下 右 上 左
vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
{
    int n = mat.size(), m = mat[0].size();
    queue<Dat> q;            // bfs queue
    vector<vector<int>> vis; // vis --是否访问过位置
    init_queue(q, vis, n, m, mat);
    while (!q.empty())
    {
        Dat cur = q.front();
        for (int k = 0; k < 4; k++)
        {
            int x = cur.i + dir1[k][0];
            int y = cur.j + dir1[k][1];
            if (x < 0 || x >= n)
                continue;
            if (y < 0 || y >= m)
                continue;
            if (vis[x][y] != -1)
                continue;
            vis[x][y] = cur.k + 1; // 下 右 上 左
            q.push(Dat(x, y, cur.k + 1));
        }
        q.pop();
    }
    return vis;
}

struct Dta
{
    Dta(int i = 0, int j = 0, int l = 0) : i(i), j(j), l(l) {}
    int i, j, l;
};

// int dir[8][2] = {
//     -1, -1, -1, 0, -1, 1,
//     0, -1, 0, 1,
//     1, -1, 1, 0, 1, 1};
int dir8[8][2] = {
    0, 1, 1, 0, 0, -1, -1, 0,
    1, -1, -1, 1, 1, 1, -1, -1};
int shortestPathBinaryMatrix(vector<vector<int>> &grid)
{
    int n = grid.size();
    vector<vector<int>> vis;
    for (int i = 0; i < n; i++)
    {
        vis.push_back(vector<int>(n));
    }
    queue<Dta> q;
    if (grid[0][0])
        return -1;
    vis[0][0] = 1;
    q.push(Dta(0, 0, 1));
    while (!q.empty())
    {
        Dta cur = q.front();
        if (cur.i == n - 1 && cur.j == n - 1)
            return cur.l;
        for (int k = 0; k < 8; k++)
        {
            int x = cur.i + dir8[k][0];
            int y = cur.j + dir8[k][1];
            if (x < 0 || x >= n)
                continue;
            if (y < 0 || y >= n)
                continue;
            if (grid[x][y])
                continue;
            if (vis[x][y])
                continue;
            vis[x][y] = 1;
            q.push(Dta(x, y, cur.l + 1));
        }
        q.pop();
    }
    return -1;
}

//  deadends=["0201", "0101", "0102", "1212", "2002"], target = "0202", output =6
// 不能用的数字，target目标 6--最小旋转次
struct Dt
{
    string s;
    int l;
    Dt(string s = "", int l = 0) : s(s), l(l) {}
};
string getS(string &s, int i, int k)
{ // 让数字0-9
    string ret = s;
    switch (k)
    {
    case 0:
        ret[i] += 1;
        break;
    case 1:
        ret[i] -= 1;
        break;
    }
    if (ret[i] < '0')
        ret[i] = '9';
    if (ret[i] > '9')
        ret[i] = '0';
    return ret;
}

int openLock(vector<string> &deadends, string target)
{
    queue<Dt> q;
    unordered_set<string> h;
    for (auto x : deadends)
        h.insert(x);
    if (h.find("0000") != h.end())
        return -1;
    h.insert("0000");
    q.push(Dt("0000", 0));
    while (!q.empty())
    {
        Dt cur = q.front();
        if (cur.s == target)
            return cur.l;
        for (int i = 0; i < 4; i++)
        {
            for (int k = 0; k < 2; k++)
            {
                string t = getS(cur.s, i, k);
                if (h.find(t) != h.end())
                    continue; // dead.. skip
                h.insert(t);
                q.push(Dt(t, cur.l + 1));
            }
        }
        q.pop();
    }
    return -1;
}

//上下左右 走1 [0,0] [m-1,n-1]  [i,] --i+j >k不能走
struct Da
{
    Da(int i = 0, int j = 0) : i(i), j(j) {}
    int i, j;
};
int dir3[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
int movingCount(int m, int n, int k)
{
    vector<int> dsum(100);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            dsum[i * 10 + j] = i + j;
        }
    }
    queue<Da> q;
    unordered_set<int> h;
    h.insert(0);
    q.push(Da(0, 0));
    int ans = 0;
    while (!q.empty())
    {
        Da cur = q.front();
        ans += 1;
        for (int i = 0; i < 4; i++)
        {
            int x = cur.i + dir3[i][0];
            int y = cur.j + dir3[i][1];
            if (x < 0 || x >= m)
                continue;
            if (y < 0 || y >= n)
                continue;
            if (h.find(x * n + y) != h.end())
                continue;
            if (dsum[x] + dsum[y] > k)
                continue;
            h.insert(x * n + y);
            q.push(Da(x, y));
        }
        q.pop();
    }
    return ans;
}

// 'x' 'o' 所有被x包围的变为x
int n, m;
int dir2[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
void dfs(int i, int j, vector<vector<char>> &board)
{
    board[i][j] = 'o';
    for (int k = 0; k < 4; k++)
    {
        if (i < 0 || j >= n)
            return;
        if (j < 0 || j >= m)
            return;
        int x = i + dir2[k][0];
        int y = j + dir2[k][1];
        if (board[x][y] != 'O')
            continue;
        dfs(x, y, board);
    }
    return;
}
void solve(vector<vector<char>> &board)
{
    n = board.size(), m = board[0].size();
    for (int i = 0; i < n; i++)
    {
        if (board[i][0] == 'O')
            dfs(i, 0, board);
        if (board[i][m - 1] == 'O')
            dfs(i, m - 1, board);
    }
    for (int j = 0; j < m; j++)
    {
        if (board[0][j] == 'O')
            dfs(0, j, board);
        if (board[n - 1][j] == 'O')
            dfs(n - 1, j, board);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] == 'O')
                board[i][j] = 'X';
            else if (board[i][j] == 'o')
                board[i][j] = 'O';
        }
    }
    return;
}

// i target
typedef pair<int, int> PII;
struct CMP
{
    int operator()(const PII &a) const
    {
        return a.first ^ a.second;
    }
};

unordered_map<PII, int, CMP> um;
int dfs1(int i, int target, vector<int> &nums)
{
    if (i == nums.size())
    {
        return target == 0;
    }
    if (um.find(PII(i, target)) != um.end())
    {
        return um[PII(i, target)];
    }
    int ans = 0;
    ans += dfs1(i + 1, target - nums[i], nums); // +
    ans += dfs1(i + 1, target + nums[i], nums); // -
    um[PII(i, target)] = ans;
    return ans;
}
int findTargetSumWays(vector<int> nums, int target)
{
    um.clear();
    return dfs1(0, target, nums);
}
//  第几个木棍， 当前桶容量
bool dfsticks(int ind, vector<int> &arr, vector<int> &ms)
{
    if (ind == -1)
        return true;
    for (int i = 0; i < 4; i++)
    {
        if (arr[i] < ms[ind]) //放不下
            continue;
        if (arr[i] == ms[ind] || arr[i] >= ms[ind] + ms[0]) // 刚好放下，余量不能小于最小的木棍
        {
            arr[i] -= ms[ind];
            if (dfsticks(ind - 1, arr, ms))
                return true;
            arr[i] += ms[ind];
        }
    }
    return false;
}
bool makesquare(vector<int> &matchsticks)
{
    sort(matchsticks.begin(), matchsticks.end());
    vector<int> arr(4);
    int sum = 0;
    for (auto x : matchsticks)
        sum += x;
    for (int i = 0; i < 4; i++)
        arr[i] = sum / 4;
    return dfsticks(matchsticks.size() - 1, arr, matchsticks);
}


// [2,3,6,7] [7] |||| [7] [2,2,3]
void dfscomb(int ind, int target,vector<int> &nums, vector<int> & buff, vector<vector<int>> &ret){
    
    if(target <0) return;
    if(target == 0) {
        ret.push_back(buff);
        return ;
    }
    if(ind == nums.size()) return;
    dfscomb(ind+1, target, nums, buff, ret);
    buff.push_back(nums[ind]);
    dfscomb(ind, target-nums[ind], nums, buff, ret);
    buff.pop_back();
    return ;
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target){
    vector<int> buff;
    vector<vector<int>> ret;
    dfscomb(0, target, candidates,buff, ret);
    return ret;
}

