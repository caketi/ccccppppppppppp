#include <algorithm>
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdint.h>
#include <string>
#include <time.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};
struct Data {
  Data(TreeNode *node, TreeNode *father, int deepth = 0)
      : node(node), deepth(deepth), father(father) {}
  TreeNode *node, *father;
  int deepth;
};

int dfs(TreeNode *root, int x, TreeNode *&father) {
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
bool isCousins(TreeNode *root, int x, int y) {
  int d1, d2;
  TreeNode *father_x = nullptr, *father_y = nullptr;
  d1 = dfs(root, x, father_x);
  d2 = dfs(root, y, father_y);
  return d1 == d2 && father_x != father_y;
}

bool isCousinsbfs(TreeNode *root, int x, int y) {
  int d1, d2;
  TreeNode *father_x = nullptr, *father_y = nullptr;
  queue<Data> q;
  q.push(Data(root, 0));
  while (!q.empty()) {
    Data cur = q.front();
    if (cur.node->val == x)
      d1 = cur.deepth, father_x = cur.father;
    if (cur.node->val == y)
      d2 = cur.deepth, father_y = cur.father;
    if (cur.node->left) {
      q.push(Data(cur.node->left, cur.node, cur.deepth + 1));
    }
    if (cur.node->right) {
      q.push(Data(cur.node->right, cur.node, cur.deepth + 1));
    }
    q.pop();
  }
  return d1 == d2 && father_x != father_y;
}

struct Dat {
  int i, j, k; // ij位置 k--位置到0的距离
  Dat(int i = 0, int j = 0, int k = 0) : i(i), j(j), k(k) {}
};
void init_queue(queue<Dat> &q, vector<vector<int>> &vis, int n, int m,
                vector<vector<int>> &mat) {
  for (int i = 0; i < n; i++) {
    vis.push_back(vector<int>());
    for (int j = 0; j < m; j++) {
      vis[i].push_back(-1);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (mat[i][j])
        continue; // 不加入1， 加入所有0位置
      vis[i][j] = 0;
      q.push(Dat(i, j, 0));
    }
  }
  return;
}
int dir1[4][2] = {0, 1, 1, 0, 0, -1, -1, 0}; // 下 右 上 左
vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
  int n = mat.size(), m = mat[0].size();
  queue<Dat> q;            // bfs queue
  vector<vector<int>> vis; // vis --是否访问过位置
  init_queue(q, vis, n, m, mat);
  while (!q.empty()) {
    Dat cur = q.front();
    for (int k = 0; k < 4; k++) {
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

struct Dta {
  Dta(int i = 0, int j = 0, int l = 0) : i(i), j(j), l(l) {}
  int i, j, l;
};

// int dir[8][2] = {
//     -1, -1, -1, 0, -1, 1,
//     0, -1, 0, 1,
//     1, -1, 1, 0, 1, 1};
int dir8[8][2] = {0, 1, 1, 0, 0, -1, -1, 0, 1, -1, -1, 1, 1, 1, -1, -1};
int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
  int n = grid.size();
  vector<vector<int>> vis;
  for (int i = 0; i < n; i++) {
    vis.push_back(vector<int>(n));
  }
  queue<Dta> q;
  if (grid[0][0])
    return -1;
  vis[0][0] = 1;
  q.push(Dta(0, 0, 1));
  while (!q.empty()) {
    Dta cur = q.front();
    if (cur.i == n - 1 && cur.j == n - 1)
      return cur.l;
    for (int k = 0; k < 8; k++) {
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

//  deadends=["0201", "0101", "0102", "1212", "2002"], target = "0202", output
//  =6
// 不能用的数字，target目标 6--最小旋转次
struct Dt {
  string s;
  int l;
  Dt(string s = "", int l = 0) : s(s), l(l) {}
};
string getS(string &s, int i, int k) { // 让数字0-9
  string ret = s;
  switch (k) {
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

int openLock(vector<string> &deadends, string target) {
  queue<Dt> q;
  unordered_set<string> h;
  for (auto x : deadends)
    h.insert(x);
  if (h.find("0000") != h.end())
    return -1;
  h.insert("0000");
  q.push(Dt("0000", 0));
  while (!q.empty()) {
    Dt cur = q.front();
    if (cur.s == target)
      return cur.l;
    for (int i = 0; i < 4; i++) {
      for (int k = 0; k < 2; k++) {
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

// 上下左右 走1 [0,0] [m-1,n-1]  [i,] --i+j >k不能走
struct Da {
  Da(int i = 0, int j = 0) : i(i), j(j) {}
  int i, j;
};
int dir3[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
int movingCount(int m, int n, int k) {
  vector<int> dsum(100);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      dsum[i * 10 + j] = i + j;
    }
  }
  queue<Da> q;
  unordered_set<int> h;
  h.insert(0);
  q.push(Da(0, 0));
  int ans = 0;
  while (!q.empty()) {
    Da cur = q.front();
    ans += 1;
    for (int i = 0; i < 4; i++) {
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
void BFS(vector<vector<int>> &mark, vector<vector<char>> &grid, int x, int y) {
  static const int dx[] = {-1, 1, 0, 0};
  static const int dy[] = {0, 0, -1, 1};
  queue<pair<int, int>> Q;
  Q.push(make_pair(x, y));
  mark[x][y] = 1;
  while (!Q.empty()) {
    x = Q.front().first;
    y = Q.front().second;
    Q.pop();
    for (int i = 0; i < 4; i++) {
      int newx = dx[i] + x;
      int newy = dy[i] + y;
      if (newx < 0 || newx >= mark.size() || newy < 0 ||
          newy >= mark[newx].size()) {
        continue;
      }
      if (mark[newx][newy] == 0 && grid[newx][newy] == '1') {
        Q.push(make_pair(newx, newy));
        mark[newx][newy] = 1;
      }
    }
  }
}
void DFS(vector<vector<int>> &mark, vector<vector<char>> &grid, int x, int y) {
  mark[x][y] = 1;
  static const int dx[] = {-1, 1, 0, 0};
  static const int dy[] = {0, 0, -1, 1};
  for (int i = 0; i < 4; i++) {
    int newx = dx[i] + x;
    int newy = dy[i] + y;
    if (newx < 0 || newx >= mark.size() || newy < 0 ||
        newy >= mark[newx].size()) {
      continue;
    }
    if (mark[newx][newy] == 0 && grid[newx][newy] == '1') {
      DFS(mark, grid, newx, newy);
    }
  }
}
int numIslands(vector<vector<char>> &grid) {
  int island_num = 0;
  vector<vector<int>> mark;
  for (int i = 0; i < grid.size(); i++) {
    mark.push_back(vector<int>());
    for (int j = 0; j < grid[i].size(); j++) {
      mark[i].push_back(0);
    }
  }
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (mark[i][j] == 0 && grid[i][j] == '1') {
        DFS(mark, grid, i, j);
        // BFS(mark, grid, i, j);
        island_num++;
      }
    }
  }
  return island_num;
}
// 'x' 'o' 所有被x包围的变为x
int n, m;
int dir2[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
void dfs(int i, int j, vector<vector<char>> &board) {
  board[i][j] = 'o';
  for (int k = 0; k < 4; k++) {
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
void solve(vector<vector<char>> &board) {
  n = board.size(), m = board[0].size();
  for (int i = 0; i < n; i++) {
    if (board[i][0] == 'O')
      dfs(i, 0, board);
    if (board[i][m - 1] == 'O')
      dfs(i, m - 1, board);
  }
  for (int j = 0; j < m; j++) {
    if (board[0][j] == 'O')
      dfs(0, j, board);
    if (board[n - 1][j] == 'O')
      dfs(n - 1, j, board);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
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
struct CMP {
  int operator()(const PII &a) const { return a.first ^ a.second; }
};

unordered_map<PII, int, CMP> um;
int dfs1(int i, int target, vector<int> &nums) {
  if (i == nums.size()) {
    return target == 0;
  }
  if (um.find(PII(i, target)) != um.end()) {
    return um[PII(i, target)];
  }
  int ans = 0;
  ans += dfs1(i + 1, target - nums[i], nums); // +
  ans += dfs1(i + 1, target + nums[i], nums); // -
  um[PII(i, target)] = ans;
  return ans;
}
int findTargetSumWays(vector<int> nums, int target) {
  um.clear();
  return dfs1(0, target, nums);
}
//  第几个木棍， 当前桶容量
bool dfsticks(int ind, vector<int> &arr, vector<int> &ms) {
  if (ind == -1)
    return true;
  for (int i = 0; i < 4; i++) {
    if (arr[i] < ms[ind]) // 放不下
      continue;
    if (arr[i] == ms[ind] ||
        arr[i] >= ms[ind] + ms[0]) // 刚好放下，余量不能小于最小的木棍
    {
      arr[i] -= ms[ind];
      if (dfsticks(ind - 1, arr, ms))
        return true;
      arr[i] += ms[ind];
    }
  }
  return false;
}
bool makesquare(vector<int> &matchsticks) {
  sort(matchsticks.begin(), matchsticks.end());
  vector<int> arr(4);
  int sum = 0;
  for (auto x : matchsticks)
    sum += x;
  for (int i = 0; i < 4; i++)
    arr[i] = sum / 4;
  return dfsticks(matchsticks.size() - 1, arr, matchsticks);
}
// n个火柴杆的总和 对4取余 == 0 -> true ，else false ，从大到小排序，先尝试大的减少回溯的可能。每次放置时，每条边上不可放置超过总和的1/4长度的
bool generateV2(int i, vector<int> &nums, int target, int bucket[]) {
  if (i >= nums.size()) {
    return bucket[0] == target && bucket[1] == target && bucket[2] == target &&
           bucket[3] == target;
  }
  for (int j = 0; j < 4; j++) {
    if (bucket[j] + nums[i] > target) {
      continue;
    }
    if (generateV2(i + 1, nums, target, bucket)) {
      return true;
    }
    bucket[j] -= nums[i];
  }
  return false;
}
bool makesquareV2(vector<int> &nums) {
  if (nums.size() < 4) {
    return false;
  }
  int sum = 0;
  for (int i = 0; i < nums.size(); i++) {
    sum += nums[i];
  }
  if (sum % 4) {
    return false;
  }
  sort(nums.rbegin(), nums.rend());
  int bucket[4] = {0};
  return generateV2(0, nums, sum / 4, bucket);
}

bool makesquareV3(vector<int> &nums) {
  if (nums.size() < 4) {
    return false;
  }
  int sum = 0;
  for (int i = 0; i < nums.size(); i++) {
    sum += nums[i];
  }
  if (sum % 4) {
    return false;
  }
  int target = sum / 4;
  vector<int> ok_subset; // 所有满足条件的一个边代表的集合
  vector<int> ok_half;
  int all = 1 << nums.size();
  for (int i = 0; i < all; i++) {
    int sum = 0;
    for (int j = 0; j < nums.size(); j++) {
      if (i & (1 << j)) {
        sum += nums[j];
      }
    }
    if (sum == target) {
      ok_subset.push_back(i);
    }
  }
  for (int i = 0; i < ok_subset.size(); i++) {
    for (int j = i + 1; j < ok_subset.size(); j++) {
      if ((ok_subset[i] & ok_subset[j]) == 0) {
        ok_half.push_back(ok_subset[i] | ok_subset[j]);
      }
    }
  }
  for (int i = 0; i < ok_half.size(); i++) {
    for (int j = i + 1; j < ok_half.size(); j++) {
      if ((ok_half[i] & ok_half[j]) == 0) {
        return true;
      }
    }
  }
  return false;
}

// [2,3,6,7] [7] |||| [7] [2,2,3]
void dfscomb(int ind, int target, vector<int> &nums, vector<int> &buff,
             vector<vector<int>> &ret) {

  if (target < 0)
    return;
  if (target == 0) {
    ret.push_back(buff);
    return;
  }
  if (ind == nums.size())
    return;
  dfscomb(ind + 1, target, nums, buff, ret);
  buff.push_back(nums[ind]);
  dfscomb(ind, target - nums[ind], nums, buff, ret);
  buff.pop_back();
  return;
}
vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
  vector<int> buff;
  vector<vector<int>> ret;
  dfscomb(0, target, candidates, buff, ret);
  return ret;
}

bool connect(const string &word1, const string &word2) {
  int cnt = 0; //word1 word2不相等字符个数
  for (int i = 0; i < word1.length(); i++) {
    if (word1[i] != word2[i]) {
      cnt++;
    }
  }
  return cnt == 1;
}
void construct_graph(string &beginWord, vector<string> &wordlist,
                     map<string, vector<string>> &graph) {
  wordlist.push_back(beginWord);
  for (int i = 0; i < wordlist.size(); i++) {
    graph[wordlist[i]] = vector<string>();
  }
  for (int i = 0; i < wordlist.size(); i++) {
    for (int j = i + 1; j < wordlist.size(); j++) {
      // 只相差一个字符，连接
      if (connect(wordlist[i], wordlist[j])) {
        graph[wordlist[i]].push_back(wordlist[j]);
        graph[wordlist[j]].push_back(wordlist[i]);
      }
    }
  }
}
int BFS_graph(string &beginword, string &endword,
              map<string, vector<string>> &graph) {
  queue<pair<string, int>> Q; // <顶点,步数>
  set<string> visit;          // 记录访问过的顶点
  Q.push(make_pair(beginword, 1)); //添加起始节点，步数1
  visit.insert(beginword);
  while (!Q.empty()) {
    string node = Q.front().first;
    int step = Q.front().second;
    Q.pop();
    if (node == endword) {
      return step; //返回步数
    }
    vector<string> &neighbors = graph[node]; // 获得node的全部邻居
    for (int i = 0; i < neighbors.size(); i++) {
      if (visit.find(neighbors[i]) == visit.end()) { // 未加入队列
        Q.push(make_pair(neighbors[i], step + 1)); //到达该节点步数+1
        visit.insert(neighbors[i]); //标记neighbors[i]已被访问
      }
    }
  }
  return 0;
}
// 返回最短路径 将普通队列更换为vector实现队列，保存所有的搜索节点--在pop节点时不会丢弃对头元素，只移动front指针
// 在队列节点中增加该节点的前驱节点在队列总的小标信息---可通过该下标找到是队列中的哪个节点搜索到的当前节点
struct Qitem {
  string node; //搜索节点
  int parent_pos; //前驱节点在队列中的位置
  int step; //到达当前节点的步数
  Qitem(string node, int parent_pos, int step)
      : node(node), parent_pos(parent_pos), step(step) {}
};
void BFS_graphV2(string &beginword, string &endword,
                 map<string, vector<string>> &graph, vector<Qitem> &Q, //使用vector实现队列，可保存所有信息
                 vector<int> &end_word_pos) {
  map<string, int> visit; //《单词，步数》
  int min_step = 0;
  Q.push_back(Qitem(beginword.c_str(), -1, 1));
  visit[beginword] = 1;
  int front = 0;
  while (front != Q.size()) {
    const string &node = Q[front].node;
    int step = Q[front].step;
    if (min_step != 0 && step > min_step) {
      break;
    }
    if (node == endword) {
      min_step = step;
      end_word_pos.push_back(front);
    }
    const vector<string> &neighbors = graph[node];
    for (int i = 0; i < neighbors.size(); i++) {
      if (visit.find(neighbors[i]) == visit.end() ||
          visit[neighbors[i]] == step + 1) {
        Q.push_back(Qitem(neighbors[i], front, step + 1));
        visit[neighbors[i]] = step + 1;
      }
    }
    front++;
  }
}
vector<vector<string>> findLadders(string beginword, string endword,
                                   vector<string> &wordlist) {
  map<string, vector<string>> graph;
  construct_graph(beginword, wordlist, graph);
  vector<Qitem> Q;
  vector<int> end_word_pos;
  BFS_graphV2(beginword, endword, graph, Q, end_word_pos);
  vector<vector<string>> result;
  for (int i = 0; i < end_word_pos.size(); i++) {
    int pos = end_word_pos[i];
    vector<string> path;
    while (pos != -1) { //没到头部
      path.push_back(Q[pos].node);
      pos = Q[pos].parent_pos;
    }
    result.push_back(vector<string>());
    for (int j = path.size() - 1; j >= 0; j--) {
      result[i].push_back(path[i]);
    }
  }
  return result;
}
struct QitemV2 {
  int x;
  int y;
  int h;
  QitemV2(int x, int y, int h) : x(x), y(y), h(h) {}
};
struct cmp {
  bool operator()(const QitemV2 &a, const QitemV2 &b) { return a.h > b.h; }
};
// 想象水从外往里流 搜索队列使用优先级队列堆，越矮的点优先级越高，最小堆
int trapRainWater(vector<vector<int>> &heightMap) {
  priority_queue<QitemV2, vector<QitemV2>, cmp> Q;
  if (heightMap.size() < 3 || heightMap[0].size() < 3) {
    return 0;
  }
  int row = heightMap.size();
  int column = heightMap[0].size();
  vector<vector<int>> mark;
  for (int i = 0; i < row; i++) {
    mark.push_back(vector<int>());
    for (int j = 0; j < column; j++) {
      mark[i].push_back(0);
    }
  }
  for (int i = 0; i < row; i++) {
    Q.push(QitemV2(i, 0, heightMap[i][0]));
    mark[i][0] = 1;
    Q.push(QitemV2(i, column - 1, heightMap[i][column - 1]));
    mark[i][column - 1] = 1;
  }
  for (int i = 1; i < column - 1; i++) {
    Q.push(QitemV2(0, i, heightMap[0][i]));
    mark[0][i] = 1;
    Q.push(QitemV2(row - 1, i, heightMap[row - 1][i]));
    mark[row - 1][i] = 1;
  }
 static const int dx[] = {-1,1,0,0};
 static const int dy[] = {0, 0, -1, 1};
 int result = 0;
 while(!Q.empty()){
    int x = Q.top().x;
    int y = Q.top().y;
    int h = Q.top().h;
    Q.pop();
    for(int i = 0; i < 4; i++){
        int newx = x + dx[i];
        int newy = y + dy[i];
        if(newx < 0 || newx >= row || newy <0 || newy>=column || mark[newx][newy]){
            continue;
        }
        if(h > heightMap[newx][newy]){ 
            result += h-heightMap[newx][newy]; //积水量是高度差
            heightMap[newx][newy] = h; //积水后上升
        }
        Q.push(QitemV2(newx, newy, heightMap[newx][newy]));
        mark[newx][newy] = 1;
    }
 }
 return result;

}