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

int findMaxValueOfEquation(vector<vector<int>> &points, int k)
{
    deque<int> q;
    q.push_back(0);
    int ans = INT32_MAX;
    for (int i = 1; i < points.size(); i++)
    {
        while (q.size() && points[i][0] - points[q.front()][0] > k)
            q.pop_front();
        if (q.size())
        {
            ans = max(ans, points[i][0] - points[q.front()][0] + points[i][1] + points[q.front()][1]);
        }
        while (q.size() && points[i][1] - points[i][0] > points[q.back()][1] - points[q.back()][0])
            q.pop_back();
        q.push_back(i);
    }
    return ans;
}

string multiplyBig(string num1, string num2)
{
    vector<int> a(num1.size()), b(num2.size()), c(a.size() + b.size() - 1);
    for (int i = 0; i < num1.size(); i++)
        a[a.size() - i - 1] = num1[i] - '0';
    for (int i = 0; i < num2.size(); i++)
        b[b.size() - i - 1] = num2[i] - '0';
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            c[i + j] += a[i] * b[j];
        }
    }
    for (int i = 0; i < c.size(); i++)
    {
        if (c[i] < 10)
            continue;
        if (i + 1 == c.size())
            c.push_back(0);
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    while (c.size() > 1 && c[c.size() - 1] == 0)
        c.pop_back(); //删除高位的0
    string ret = "";
    for (int i = c.size() - 1; i >= 0; i--)
        ret += c[i] + '0';
    return ret;
}

class permute
{
    vector<vector<int>> premute(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        do
        {
            ret.push_back(nums);
        } while (next_permutation(nums.begin(), nums.end()));
        return ret;
    }
};

class ipchangemake
{
    void dfs(string &s, int k, int ind, vector<string> &ret)
    {
        if (ind >= s.size())
            return;
        if (k == 4)
        {
            int num = 0;
            if (s.size() - ind > 1 && s[ind] == '0')
                return;
            for (int i = ind; i < s.size(); i++)
            {
                num = num * 10 + s[i] - '0';
                if (num > 255)
                    return;
            }
            ret.push_back(s);
            return;
        }
        for (int i = ind, num = 0; i < s.size(); i++)
        {
            num = num * 10 + s[i] - '0';
            if (num > 255)
                return;
            if (i - ind >= 1 && s[ind] == '0')
                return;
            s.insert(i + 1, ".");
            dfs(s, k + 1, i + 2, ret);
            s.erase(i + 1, 1);
        }
        return;
    }
    vector<string> restoreIpAddresses(string s)
    {
        vector<string> ret;
        dfs(s, 1, 0, ret);
        return ret;
    }
};

int jump(vector<int> &nums)
{
    if (nums.size() <= 1)
        return 0;
    int pre = 1, pos = nums[0], cnt = 1;
    while (pos + 1 < nums.size())
    {
        int j = pre;
        for (int i = pre + 1; i <= pos; i++)
        {
            if (i + nums[i] > j + nums[j])
                j = i;
        }
        pre = pos + 1, pos = j + nums[j];
        cnt += 1;
    }
    return cnt;
}

class sl
{
    int f(vector<int> &nums, int x)
    {
        int cnt = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            cnt += nums[i] / x + !!(nums[i] % x) - 1;
        }
        return cnt;
    }
    int bs(vector<int> &nums, int l, int r, int n)
    {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        if (f(nums, mid) <= n)
            r = mid;
        else
            l = mid + 1;
        return bs(nums, l, r, n);
    }
    int miniumSize(vector<int> &nums, int maxOperations)
    {
        int l = 1, r;
        for (auto x : nums)
            r = max(r, x);
        return bs(nums, l, r, maxOperations);
    }
};

class So{
    typedef pair<int, int> op;
    op getNext(int k, int x, int X, int y, int Y){
        switch(k){
            case 0: return op(0,y);
            case 1: return op(x,0);
            case 2: {
                int delta = min(x, Y-y);
                return op(x-delta, y+delta);
            }
            case 3: {
                int delta = min(X-x,y);
                return op(x+delta, y-delta);
            }
            case 4: return op(X,y);
            case 5: return op(x,Y);
        }
        return op(0,0);
    }
    bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity){
        unordered_set<op> vis;
        queue<op> q;
        vis.insert(op(0,0));
        q.push(op(0,0));
        while(!q.empty()){
            op cur = q.front();
            if(cur.first+cur.second == targetCapacity) return true;
            q.pop();
            for(int i = 0; i< 6;i++){
                op temp = getNext(i, cur.first, jug1Capacity, cur.second, jug2Capacity);
                if(vis.find(temp) != vis.end()) continue;
                vis.insert(temp);
                q.push(temp);
            }
        }
        return false;
    }
};

int candy(vector<int> &ratings)
{
    vector<int> l(ratings.size()), r(ratings.size());
    for (int i = 0, j = 1; i < l.size(); i++)
    {
        if (i && ratings[i] > ratings[i - 1])
            j += 1;
        else
            j = 1;
        l[i] = j;
    }
    for (int i = r.size() - 1, j = 1; i >= 0; i--)
    {
        if (i < r.size() - 1 && ratings[i] > ratings[i + 1])
            j += 1;
        else
            j = 1;
        r[i] = j;
    }
    int ans = 0;
    for (int i = 0; i < l.size(); i++)
        ans += max(l[i], r[i]);
    return ans;
}

//
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
int max_k, va;
void dfs(TreeNode *root, int k)
{
    if (root == nullptr)
        return;
    if (k > max_k)
    {
        max_k = k, va = root->val;
    }
    dfs(root->left, k + 1);
    dfs(root->right, k + 1);
    return;
}
int findBottomLeftValue(TreeNode *root)
{
    max_k = -1, va = 0;
    dfs(root, 0);
    return va;
}

// 区间最大值最小值差<=limit, 返回最大长度
bool check(vector<int> &nums, int k, int limit)
{
    deque<int> qmin, qmax;
    for (int i = 0; i < nums.size(); i++)
    {
        while (qmin.size() && nums[i] < nums[qmin.back()])
            qmin.pop_back();
        while (qmax.size() && nums[i] > nums[qmax.back()])
            qmax.pop_back();
        qmin.push_back(i);
        qmax.push_back(i);
        if (i + 1 < k)
            continue;
        if (i - qmin.front() == k)
            qmin.pop_front();
        if (i - qmax.front() == k)
            qmax.pop_front();
        if (nums[qmax.front()] - nums[qmin.front()] <= limit)
            return true;
    }
    return false;
}

int bs(vector<int> &nums, int l, int r, int limit)
{
    if (l == r)
        return l;
    int mid = (l + r + 1) >> 1;
    if (check(nums, mid, limit))
        l = mid;
    else
        r = mid - 1;
    return bs(nums, l, r, limit);
}
int longsetSubarray(vector<int> &nums, int limit)
{
    return bs(nums, 0, nums.size(), limit);
}

int shortestSubarray(vector<int> &nums, int k)
{
    deque<int> q;
    vector<int> sum(nums.size() + 1);
    sum[0] = 0;
    for (int i = 0; i < nums.size(); i++)
        sum[i + 1] = sum[i] + nums[i];
    q.push_back(0);
    int pos = -1, ans = -1;
    for (int i = 1; i < sum.size(); i++)
    {
        while (q.size() && sum[i] - sum[q.front()] >= k)
        {
            pos = q.front();
            q.pop_front();
        }
        if (pos != -1 && (i - pos < ans || ans == -1))
            ans = i - pos;
        while (q.size() && sum[i] < sum[q.back()])
            q.pop_back();
        q.push_back(i);
    }
    return ans;
}

class MaxQueue
{
public:
    deque<int> q, mq;
    MaxQueue() {}
    int max_value()
    {
        if (mq.size() == 0)
            return -1;
        return mq.front();
    }
    void push_back(int value)
    {
        q.push_back(value);
        while (q.size() && value > mq.back())
            mq.pop_back();
        mq.push_back(value);
        return;
    }
    int pop_front()
    {
        if (q.size() == 0)
            return -1;
        if (q.front() == mq.front())
            mq.pop_front(); // q:mq,我走了 mq: ogod, q!!!!
        int ret = q.front();
        q.pop_front();
        return ret;
    }
};

vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
    deque<int> q;
    vector<int> ret;
    for (int i = 0; i < nums.size(); i++)
    {
        while (q.size() && nums[i] > nums[q.back()])
            q.pop_back();
        q.push_back(i);
        if (i - q.front() == k)
            q.pop_front();
        if (i + 1 < k)
            continue;
        ret.push_back(nums[q.front()]);
    }
    return ret;
}

int main()
{
    // 8 3
    // 1 3 -1 -3 5 3 6 7
    vector<int> arr;
    int n, k;
    cin >> n >> k;
    for (int i = 0, a; i < n; i++)
    {
        cin >> a;
        arr.push_back(a);
    }
    deque<int> q;
    cout << "min in ()" << endl;
    for (int i = 0; i < n; i++)
    {
        while (q.size() && arr[q.back()] > arr[i])
            q.pop_back();
        q.push_back(i);
        if (i - q.front() == k)
            q.pop_front();
        if (i + 1 < k)
            continue;
        if (i + 1 > k)
            cout << " ";
        cout << arr[q.front()];
    }
    cout << endl;
    q.clear();
    cout << "max in ()" << endl;
    for (int i = 0; i < n; i++)
    {
        while (q.size() && arr[q.back()] < arr[i])
            q.pop_back();
        q.push_back(i);
        if (i - q.front() == k)
            q.pop_front();
        if (i + 1 < k)
            continue;
        if (i + 1 > k)
            cout << " ";
        cout << arr[q.front()];
    }
    cout << endl;

    // 5 || 3 1 5 2 4 || 5 2 4 3 1
    int n1;
    cin >> n1;
    vector<int> a1(n1), b1(n1);
    for (int i = 0; i < n1; i++)
        cin >> a1[i];
    for (int i = 0; i < n1; i++)
        cin >> b1[i];
    deque<int> q1, q2;
    int p;
    for (p = 0; p < n; p++)
    {
        while (q1.size() && a1[p] < q1.back())
            q1.pop_back();
        while (q2.size() && b1[p] < q2.back())
            q2.pop_back();
        q1.push_back(a1[p]);
        q2.push_back(b1[p]);
        if (q1.size() != q2.size())
            break;
    }
    cout << p << endl;
    return 0;
}
