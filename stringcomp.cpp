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
int brute_force(const char *text, const char *pattern)
{
    for (int i = 0; text[i]; ++i)
    {
        int flag = 1;
        for (int j = 0; pattern[j]; ++j)
        {
            if (text[i + j] == pattern[j])
                continue;
            flag = 0;
            break;
        }
        if (flag)
            return true;
    }
    return -1;
}
// 状态机--给个字符，j变
void GetNext(const char *pattern, int *next)
{
    next[0] = -1;
    for (int i = 1, j = -1; pattern[i]; ++i)
    {
        while (j != -1 && pattern[j + 1] - pattern[j])
            j = next[j];
        if (pattern[j + 1] == pattern[i])
            j += 1;
        next[i] = j;
    }
    return;
}

int GetNextJ(char ch, const char *pattern, int *next, int j)
{
    while (j != -1 && ch - pattern[j + 1])
        j = next[j];
    if (ch == pattern[j + 1])
        j += 1;
    return j;
}

int kmp(const char *text, const char *pattern)
{
    int n = strlen(pattern);
    int *next = (int *)malloc(sizeof(int) * n);
    GetNext(pattern, next);
    for (int i = 0, j = -1; text[i]; i++)
    {
        GetNextJ(text[i], pattern, next, j);
        // while (j != -1 && text[i] - pattern[j + 1])
        //     j = next[j];
        // if (text[i] == pattern[j + 1])
        //     j += 1;
        if (pattern[j + 1] == 0)
            return i - j;
    }
    return -1;
}
// 文本串必须已知
int sunday(const char *text, const char *pattern)
{
#define BASE 256
    int n = strlen(text), m, last_pos[BASE];
    for (int i = 0; i < BASE; i++)
        last_pos[i] = -1;
    for (m = 0; pattern[m]; ++m) // m-=- pattern len
        last_pos[pattern[m]] = m;
    for (int i = 0; i + m <= n; i += (m - last_pos[text[i + m]])) // 最后位置不等，向后推pattern.len
    {
        int flag = 1;
        for (int j = 0; pattern[j]; j++)
        {
            if (text[i + j] == pattern[j])
                continue;
            flag = 0;
            break;
        }
        if (flag)
            return i;
    }
    return -1;
}

int GetNextP(char ch, int *code, int p)
{
    return (p << 1 | 1) & code[ch];
}
// 左-右 低-高 和kmp同适用流数据处理，给个字符状态变（p变，next变）
// 每个位置允许重复字符
int shift_and(const char *text, const char *pattern)
{
    int code[256] = {0};
    int n = 0;
    for (n; pattern[n]; ++n)
        code[pattern[n]] |= (1 << n);
    int p = 0;
    for (int i = 0; text[i]; i++)
    {
        p = GetNextP(text[i], code, p);
        // p = (p << 1 | 1) & code[text[i]];
        if (p & (1 << (n - 1)))
            return i - n + 1;
    }
    return -1;
}
#define TEST(func, s1, s2)                                        \
    {                                                             \
        printf("%s(%s, %s) = %d\n", #func, s1, s2, func(s1, s2)); \
    }

bool repeatedSubstringPattern(string s)
{
    int pos = 0;
    char c = s[0];
    while ((pos = s.find(c, pos + 1)) != s.npos)
    {
        if (s.size() % pos != 0)
            continue;
        int flag = 0;
        for (int i = pos; i < s.size();)
        {
            for (int j = 0; j < pos; j++)
            {
                if (s[i] == s[j])
                {
                    i++;
                }
                else
                {
                    i++;
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 0)
            return true;
    }
    if (s.size() % pos != 0)
        return false;
    return true;
}
// "abab" true
bool repeatedSubstringPatternKMP(string s)
{
    int n = s.size(), j = -1;
    vector<int> next(n);
    next[0] = -1;
    for (int i = 1; i < s.size(); i++)
    {
        while (j != -1 && s[j + 1] != s[i])
            j = next[j];
        if (s[j + 1] == s[i])
            j++;
        next[i] = j;
    }
    return (next[n - 1] != -1) && (n % (n - (next[n - 1] + 1)) == 0);
}

// s = "level" "l"
string longestPrefix(string s)
{
    int n = s.size(), j = -1;
    vector<int> next(n);
    next[0] = -1;
    for (int i = 1; i < n; i++)
    {
        while (j != -1 && s[j + 1] != s[i])
            j = next[j];
        if (s[j + 1] == s[i])
            j += 1;
        next[i] = j;
    }
    return s.substr(0, next[n - 1] + 1);
}

string shortestPalindrome(string s)
{
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    // aabc#cbaa
    rev_s = s + "#" + rev_s;

    int n = rev_s.size(), j = -1;
    vector<int> next(n);
    next[0] = -1;
    for (int i = 1; i < n; i++)
    {
        while (j != -1 && rev_s[j + 1] != rev_s[i])
            j = next[i];
        if (rev_s[j + 1] == rev_s[i])
            j++;
        next[i] = j;
    }

    rev_s = s.substr(next[rev_s.size() - 1] + 1, s.size());
    reverse(rev_s.begin(), rev_s.end());
    return rev_s + s;
}
int main()
{
    char s1[100], s2[100];
    while (cin >> s1 >> s2)
    {
        TEST(brute_force, s1, s2);
    }
    return 0;
}

string getNewString(string &s)
{
    string new_s = "#";
    for (int i = 0; s[i]; i++)
    {
        (new_s += s[i]) += "#";
    }
    return new_s;
}
// 5.   s"babad" "bab"
string longestPalindromekk(string s)
{
    string ns = getNewString(s);
    vector<int> d(ns.size()); // 记录每一个位置的最长回文半径
    int l = 0, r = -1;        // 最远的r

    for (int i = 0; ns[i]; i++)
    {
        if (i > r) //当前遍历的i不在任何一个回文区间
        {
            d[i] = 1;
        }
        else
        {
            d[i] = min(r - 1, d[l + r - i]);
        }
        while (i - d[i] >= 0 && ns[i - d[i]] == ns[i + d[i]])
        {
            d[i]++;
        }
        if (i + d[i] > r && i - d[i] > 0)
        {
            l = i - d[i];
            r = i + d[i];
        }
    }
    string ret;
    int tmp = 0;
    for (int i = 0; ns[i]; i++)
    {
        if (tmp >= d[i])
            continue;
        tmp = d[i];
        ret = "";
        for (int j = i - d[i] + 1; j < i + d[i]; j++)
        {
            if (ns[j] == '#')
                continue;
            ret += ns[j];
        }
    }
    return ret;
}

int strStr(string haystack, string needle)
{
    int ind[128];
    for (int i = 0; i < 128; i++)
        ind[i] = -1;
    for (int i = 0; needle[i]; i++)
        ind[needle[i]] = i;
    int i = 0;
    while (i + needle.size() <= haystack.size())
    {
        int flag = 1;
        for (int j = 0; needle[j]; j++)
        {
            if (haystack[i + j] == needle[j])
                continue;
            flag = 0;
            break;
        }
        if (flag)
            return i;
        i += (needle.size() - ind[haystack[i + needle.size()]]);
    }
    return -1;
}
// "abcabcbb" 3 "abc"无重复最长子串
bool check(int l, string &s) // l-窗口大小
{
    int cnt[256] = {0}, k = 0;
    for (int i = 0; s[i]; i++)
    {
        if (cnt[s[i]] == 0)
            k += 1;
        cnt[s[i]] += 1;

        if (i >= l) //超出窗口大小
        {
            cnt[s[i - l]] -= 1;
            if (cnt[s[i - l]] == 0)
                k -= 1;
        }
        if (k == l)
            return true;
    }
    return false;
}
int lengthOfLongestSubstring(string s)
{
    if (s == "")
        return 0;
    int head = 1, tail = s.size(), mid;
    while (head < tail)
    {
        mid = (head + tail + 1) >> 1;
        if (check(mid, s))
            head = mid;
        else
            tail = mid - 1;
    }
    return head;
}
// 最长公共前缀
// strs = {"flower", "flow", "flight"}  "fl"
string Compare(string &a, string &b)
{
    string ret = "";
    for (int i = 0; a[i]; i++)
    {
        if (i == b.size() || a[i] != b[i])
            return ret;
        ret += a[i];
    }
    return ret;
}
string longestCommonPrefix(vector<string> &strs)
{
    string ret = strs[0];
    for (int i = 1; i < strs.size(); i++)
    {
        ret = Compare(ret, strs[i]);
    }
    return ret;
}

// 一次编辑 f = "pale" s = "ple" output= True
bool oneEditAway(string first, string second)
{
    if (first.size() < second.size())
        swap(first, second);
    int n = first.size(), m = second.size();
    if (abs(n - m) > 1)
        return false;
    if (abs(n - m) == 0)
    {
        for (int i = 0, j = 0; i < n; i++)
        {
            if (first[i] == second[i])
                continue;
            j += 1;
            if (j == 2)
                return false;
        }
        return true;
    }
    int i = 0, j = m - 1;
    while (i <= j && first[i] == second[i])
        i++;
    while (i <= j && first[j + 1] == second[j])
        --j;
    return i > j;
}