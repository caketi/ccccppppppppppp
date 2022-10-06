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

class UnionSet
{
public:
    int *fa, *size, n, *cnt;
    UnionSet(int n) : n(n)
    {
        fa = new int[n + 1];
        size = new int[n + 1];
        cnt  = new int[n+1];
        for (int i = 0; i <= n; i++)
        {
            fa[i] = i;
            size[i] = 1;
            cnt[i] = 1;
        }
    }
    int find(int x) // 找爸爸
    {
        // return fa[x] = (fa[x] == x ? x: find(fa[x]));
        if (fa[x] == x)
            return x;
        return find(fa[x]);
        // int root = find(fa[x]); // 路径压缩
        // return root;
    }

    void merge(int a, int b)
    {
        // fa[find(a)] = find(b);
        int ra = find(a);
        int rb = find(b);
        if (ra == rb)
            return;
        if (size[ra] < size[rb])
        {
            fa[ra] = rb;
            size[rb] += size[ra];
            cnt[rb] += cnt[ra];
        }
        else
        {
            fa[rb] = ra;
            size[ra] += size[rb];
            cnt[rb] += cnt[ra];
        }
        return;
    }
};

int findCircleNum(vector<vector<int> > &isConnected)
{
    int n = isConnected.size();
    UnionSet u(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (isConnected[i][j])
                u.merge(i, j);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (u.find(i) == i)
            ans += 1;
    }
    return ans;
}

// a==b   a!=b 是否冲突--- 连通性
bool equationsPossible(vector<string> &equations)
{
    UnionSet u(26);
    for (auto s : equations)
    {
        if (s[1] == '!')
            continue;
        int a = s[0] - 'a';
        int b = s[3] - 'a';
        u.merge(a, b);
    }
    for (auto s : equations)
    {
        if (s[1] == '=')
            continue;
        int a = s[0] - 'a';
        int b = s[3] - 'b';
        if (u.find(a) == u.find(b))
            return false;
    }
    return true;
}

int numIslands(vector<vector<char> > &grid)
{
    int n = grid.size(), m = grid[0].size();
    UnionSet u(n * m);
#define ind(i, j) ((i)*m + (j)) // 计算索引
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '0')
                continue;
            // 当前点是1， 连接上左就行
            if (i > 0 && grid[i - 1][j] == '1')
                u.merge(ind(i, j), ind(i - 1, j));
            if (j > 0 && grid[i][j - 1] == '1')
                u.merge(ind(i, j), ind(i, j - 1));
        }
    }
    // 完成连接操作
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '1' && u.find(ind(i, j)) == ind(i, j))
                ans += 1;
        }
    }
#undef ind
    return ans;
}

// 连通网络的操作次数
int makeConnected(int n, vector<vector<int> > &connections)
{
    if (connections.size() < n - 1)
        return -1;
    UnionSet u(n);
    for (auto e : connections)
    {
        int a = e[0];
        int b = e[1];
        u.merge(a, b);
    }
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (u.find(i) == i)
            cnt += 1;
    }
    return cnt - 1;
}


int longestConsecutive(vector<int>& nums){
    map<int,int> ind;
    UnionSet u(nums.size());
    for(int i = 0; i < nums.size(); i++){
        int x = nums[i];
        if(ind.find(x) != ind.end()) continue;
        if(ind.find(x-1) != ind.end()) {
            u.merge(i, ind[x+1]);
        }
        if(ind.find(x+1) != ind.end()){
            u.merge(i, ind[x+1]);
        }
        ind[x] = i; // 记录数字的索引，用索引来连线
    }
    int ans = 0;
    for(int i  = 0; i < nums.size(); i++){
        if(u.find(i) == i && u.cnt[i] > ans) ans = u.cnt[i];
    }
    return ans;
}

vector<int> findRedundantConnection(vector<vector<int> > &edges)
{
    UnionSet u(edges.size());
    for (auto e : edges)
    {
        int a = e[0];
        int b = e[1];
        if (u.find(a) == u.find(b))
            return e;
        u.merge(a, b);
    }
    return vector<int>();
}
// s = "dcab", pairs=([0,3], [1,2])
// "bacd"
string smallestStringWithSwaps(string s, vector<vector<int> >& pairs){
    UnionSet u(s.size());
    priority_queue<char, vector<char>, greater<char> > h[s.size()];
    for(auto p : pairs){ // 并查集连起来
        int i = p[0];
        int j = p[1];
        u.merge(i,j);
    }
    for(int i = 0; i <s.size(); i++){
        h[u.find(i)].push(s[i]); // 找到字符的爸爸
    }
    string ret = "";
    for(int i = 0; i <s.size(); i++){ // 从字符所在的小顶堆中取出，单出
        ret += h[u.find(i)].top(); 
        h[u.find(i)].pop();
    }
    return ret;
}


int removeStones(vector<vector<int> >& stones){
    UnionSet u(stones.size());
    map<int, int> ind_x, ind_y;
    for(int i = 0; i < stones.size(); i++){
        int x = stones[i][0];
        int y = stones[i][1];
        if(ind_x.find(x) != ind_x.end()) {
            u.merge(i, ind_x[x]);
        }
        if( ind_y.find(y) != ind_y.end()){
            u.merge(i, ind_y[y]);
        }
        ind_x[x] = i;
        ind_y[y] = i;
    }
    int  cnt = 0;
    for(int i = 0; i< stones.size(); i++){
        if(u.find(i) == i) cnt+=i;
    }
    return stones.size() - cnt;
}