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

struct node
{
    char ch;
    int freq;
    node *left;
    node *right;
    node(int freq = 0, char ch = 0) : freq(freq), ch(ch), left(nullptr), right(nullptr) {}
    node(int freq = 0, node *left = nullptr, node *right = nullptr,  char ch = 0) : left(left), right(right), freq(freq), ch(ch) {}
};
struct CMP
{
    bool operator()(const node *a, const node *b) const
    {
        return a->freq < b->freq;
    }
};
void extract_code(node *root, string prefix, vector<string> &code)
{
    if (root->ch != 0)
    {
        code[root->ch] = prefix;
        return;
    }
    extract_code(root->left, prefix + '0', code);
    extract_code(root->right, prefix + '1', code);
    return;
}
// 3
// a 2222
// b 1212
// c 2121
int main()
{
    int n, freq, freq_arr[128];
    char ch;
    cin >> n;
    multiset<node *, CMP> s;

    for (int i = 0; i < n; i++)
    {
        cin >> ch >> freq;
        freq_arr[ch] = freq;
        s.insert(new node(freq, ch));
    }
    while (s.size() > 1)
    {
        node *a = *(s.begin());
        s.erase(s.begin());
        node *b = *(s.begin());
        s.erase(s.begin());
        s.insert(new node(a->freq + b->freq, a, b));
    }
    node *root = *(s.begin());
    vector<string> code(128);
    extract_code(root, "", code);
    for (int i = 0; i < 128; i++)
    {
        if (code[i] == "")
            continue;
        // cout << char(i) << " : " << code[i] << endl;
        printf("%c(%6d) : %s\n", i ,freq_arr[i], code[i].c_str());
    }
    // for (auto x : s)
    // {
    //     cout << x->freq << endl;
    // } 
    return 0;
}

// sticks = {2,4,3}  14
int connectSticks(vector<int> &sticks)
{
    multiset<int> s;
    for (auto x : sticks)
        s.insert(x);
    int ans = 0;
    while (s.size() - 1)
    {
        int a = *(s.begin());
        s.erase(s.begin());
        int b = *(s.begin());
        s.erase(s.begin());
        s.insert(a + b);
        ans += a + b;
    }
    return ans;
}
// 676. 魔法字典
class Node
{
public:
    Node()
    {
        flag = false;
        for (int i = 0; i < 26; i++)
            next[i] = nullptr;
    }
    bool flag;
    Node *next[26];
};
class Trie
{
private:
    Node root;

public:
    void insert(string &s)
    {
        Node *p = &root;
        for (auto x : s)
        {
            int ind = x - 'a';
            if (p->next[ind] == nullptr)
                p->next[ind] = new Node();
            p = (Node *)p->next;
        }
        p->flag = true;
        return;
    }
    bool __search(string &s, int pos, Node *p, int n)
    {
        if (pos == s.size())
            return p->flag && n == 0;
        int ind = s[pos] - 'a';
        if (p->next[ind] && __search(s, pos + 1, p->next[ind], n))
            return true;
        if (n)
        {
            for (int i = 0; i < 26; i++)
            {
                if (i == ind || p->next[i] == nullptr)
                    continue;
                if (__search(s, pos + 1, p->next[i], n - 1))
                    return true;
            }
        }
        return false;
    }
    bool search(string &s, int n)
    {
        return __search(s, 0, &root, n);
    }
};

int pre_ind;
bool judge(vector<int> &preorder, int l, int r)
{
    if (r - l < 1)
        return true;

    int ind = l + 1;
    while (ind < r && preorder[ind] < preorder[l])
        ind += 1;

    if (!judge(preorder, l + 1, ind))
        return false;                                     // root left  right
    if (pre_ind != -1 && preorder[l] < preorder[pre_ind]) // ind->first right child indx
        return false;
    pre_ind = l;
    if (!judge(preorder, ind, r))
        return false;
    return true;
}

bool verifyPreorder(vector<int> &preorder)
{
    pre_ind = -1;
    return judge(preorder, 0, preorder.size());
}

vector<int> sunday(string &s, string &t)
{
    vector<int> ret;
    int last_ind[128] = {0};
    for (int i = 0; t[i]; i++)
        last_ind[t[i]] = i + 1; // i记录第几位 从一开始
    int lens = s.size(), lent = t.size(), i = 0;
    while (i + lent <= lens)
    {
        bool flag = true;
        for (int j = 0; j < lent; j++)
        {
            if (s[i + j] == t[j])
                continue;
            flag = false;
            break;
        }
        if (flag)
        {
            ret.push_back(i);
            i += 1;
        }
        else
        {
            i += lent - last_ind[s[i + lent]] + 1;
        }
    }

    return ret;
}
// big = "mississippi"   smalls = {"is", "ppi", "hi", "sis", "i", "ssippi"}
// [[1,4], [8], [], [3], [1,4,7,10],[5]]
vector<vector<int>> multiSearch(string big, vector<string> &smalls)
{
    vector<vector<int>> ret;
    for (auto s : smalls)
    {
        ret.push_back(sunday(big, s));
    }
    return ret;
}

int longestValidParenthese(string s)
{
    if (s == "")
        return 0;
    int ans = 0, __dp[s.size() + 5], *dp = __dp + 3;
    memset(__dp, 0, sizeof(__dp));
    dp[0] = 0;
    for (int i = 1; i < s.size(); i++)
    {
        dp[i] = 0;
        if (s[i] == '(')
            continue;
        if (s[i - 1] == '(')
            dp[i] = dp[i - 2] + 2;
        else
        {
            int j = i - dp[i - 1] - 1;
            if (j < 0 || s[j] == ')')
                continue;
            dp[i] = dp[i - 1] + 2 + dp[j - 1];
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

// 最小覆盖子串--76. 滑动
string minWindow(string s, string t)
{
    int cnt = 0, cnts[128] = {0};
    for (auto x : t)
    {
        cnts[x] -= 1;
        if (cnts[x] == -1)
            cnt += 1;
    }
    int ans_len = s.size() + 1, l = 0, r = 0;
    string ans = "";
    while (r <= s.size())
    {
        if (cnt)
        {
            if (r == s.size())
                break;
            cnts[s[r]] += 1;
            if (cnts[s[r]] == 0)
                cnt -= 1;
            r += 1;
        }
        else
        {
            cnts[s[l]] -= 1;
            if (cnts[s[l]] == -1)
                cnt += 1;
            l += 1;
        }
        if (cnt == 0 && r - l < ans_len)
        {
            ans_len = r - l;
            ans = s.substr(l, r - l);
        }
    }
    return ans;
}
// intput: 2 output: [0,1,3,2]
vector<int> grayCode(int n)
{
    vector<int> ret(1 << n);
    if (n == 0)
    {
        ret[0] = 0;
        return ret;
    }
    // 0区域 1区域
    vector<int> code_n_1 = grayCode(n - 1);
    int len_n_1 = code_n_1.size();
    for (int i = 0; i < len_n_1; i++)
    {
        ret[i] = code_n_1[i] << 1;
        ret[2 * len_n_1 - i - 1] = code_n_1[i] << 1 | 1; //对称0---n n---0
    }
    return ret;
}

bool valid_ipv4(string &s, int l, int r)
{
    if (r - l <= 0 || r - l > 3)
        return false;
    if (r - l > 1 && s[l] == '0')
        return false;
    int num = 0;
    for (int i = l; i < r; i++)
    {
        if (s[i] < '0' || s[i] > '9')
            return false;
        num = num * 10 + s[i] - '0';
    }
    return num < 256;
}
bool valid_ipv6(string &s, int l, int r)
{
    if (r - l <= 0 || r - l > 4)
        return false;
    for (int i = l; i < r; i++)
    {
        if (s[i] <= '9' && s[i] >= '0')
            continue;
        if (s[i] <= 'F' && s[i] >= 'A')
            continue;
        if (s[i] <= 'f' && s[i] >= 'a')
            continue;
        return false;
    }
    return true;
}
string validIPAddress(string QueryIP)
{
    int flag = 0, pre_ind = 0, cnt = 0;
    for (int i = 0; i < QueryIP.size() && flag != -1; i++)
    {
        // ipv4
        if (QueryIP[i] == '.')
        {
            if (flag == 0)
                flag = 1;
            if (flag != 1 || !valid_ipv4(QueryIP, pre_ind, i))
            {
                flag = -1;
                break;
            }
            cnt += 1;
            pre_ind = i + 1;
        }
        if (QueryIP[i] == ':')
        {
            if (flag == 0)
                flag = 2;
            if (flag != 2 || !valid_ipv6(QueryIP, pre_ind, i))
            {
                flag = -1;
                break;
            }
            cnt += 1;
            pre_ind = i + 1;
        }
    }
    if (flag == 1 && cnt == 4)
        return "IPv4";
    if (flag == 2 && cnt == 8)
        return "IPv6";
    return "Neither";
}