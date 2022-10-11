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
#include <string>
#include <time.h>
#include <unordered_map>
#include <vector>

using namespace std;
int brute_force(const char *text, const char *pattern) {
  for (int i = 0; text[i]; ++i) {
    int flag = 1;
    for (int j = 0; pattern[j]; ++j) {
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
void getNext(int *next, const string &s) {
  next[0] = -1;
  int j = -1;
  for (int i = 1; i < s.size(); i++) {
    while (j >= 0 && s[i] != s[j + 1]) // 前后缀不相同了
    {
      j = next[j]; // 回退
    }
    if (s[i] == s[j + 1]) {
      j++;
    }
    next[i] = j;
  }
}
bool repeatedSubstringPattern(string s) {
  if (s.size() == 0) {
    return false;
  }
  int next[s.size()];
  getNext(next, s);
  int len = s.size();
  if (next[len - 1] != -1 &&
      len % (len - (next[len - 1] + 1)) ==
          0) { // next[len - 1] + 1---最长相等前后缀的长度
    return true;
  }
  return false;
}

// 状态机--给个字符，j变
void GetNext(const char *pattern, int *next) {
  next[0] = -1;
  for (int i = 1, j = -1; pattern[i]; ++i) {
    while (j != -1 && pattern[j + 1] - pattern[j])
      j = next[j];
    if (pattern[j + 1] == pattern[i])
      j += 1;
    next[i] = j;
  }
  return;
}

int GetNextJ(char ch, const char *pattern, int *next, int j) {
  while (j != -1 && ch - pattern[j + 1])
    j = next[j];
  if (ch == pattern[j + 1])
    j += 1;
  return j;
}

int kmp(const char *text, const char *pattern) {
  int n = strlen(pattern);
  int *next = (int *)malloc(sizeof(int) * n);
  GetNext(pattern, next);
  for (int i = 0, j = -1; text[i]; i++) {
    GetNextJ(text[i], pattern, next, j);
    // while (j != -1 && text[i] - pattern[j + 1])
    //     j = next[j];
    // if (text[i] == pattern[j + 1])
    //     j += 1;
    if (pattern[j + 1] ==
        0) // 如果j指向了模式串t的末尾，那么就说明模式串t完全匹配文本串s里的某个子串了。
      return i - j;
  }
  return -1;
}
// 文本串必须已知
int sunday(const char *text, const char *pattern) {
#define BASE 256
  int n = strlen(text), m, last_pos[BASE];
  for (int i = 0; i < BASE; i++)
    last_pos[i] = -1;
  for (m = 0; pattern[m]; ++m) // m-=- pattern len
    last_pos[pattern[m]] = m;
  for (int i = 0; i + m <= n;
       i += (m - last_pos[text[i + m]])) // 最后位置不等，向后推pattern.len
  {
    int flag = 1;
    for (int j = 0; pattern[j]; j++) {
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

int GetNextP(char ch, int *code, int p) { return (p << 1 | 1) & code[ch]; }
// 左-右 低-高 和kmp同适用流数据处理，给个字符状态变（p变，next变）
// 每个位置允许重复字符
int shift_and(const char *text, const char *pattern) {
  int code[256] = {0};
  int n = 0;
  for (; pattern[n]; ++n)
    code[pattern[n]] |= (1 << n);
  int p = 0;
  for (int i = 0; text[i]; i++) {
    p = GetNextP(text[i], code, p);
    // p = (p << 1 | 1) & code[text[i]];
    if (p & (1 << (n - 1)))
      return i - n + 1;
  }
  return -1;
}
#define TEST(func, s1, s2)                                                     \
  { printf("%s(%s, %s) = %d\n", #func, s1, s2, func(s1, s2)); }

bool repeatedSubstringPatternV2(string s) {
  int pos = 0;
  char c = s[0];
  while ((pos = s.find(c, pos + 1)) != s.npos) {
    if (s.size() % pos != 0)
      continue;
    int flag = 0;
    for (int i = pos; i < s.size();) {
      for (int j = 0; j < pos; j++) {
        if (s[i] == s[j]) {
          i++;
        } else {
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
bool repeatedSubstringPatternKMP(string s) {
  int n = s.size(), j = -1;
  vector<int> next(n);
  next[0] = -1;
  for (int i = 1; i < s.size(); i++) {
    while (j != -1 && s[j + 1] != s[i])
      j = next[j];
    if (s[j + 1] == s[i])
      j++;
    next[i] = j;
  }
  return (next[n - 1] != -1) && (n % (n - (next[n - 1] + 1)) == 0);
}

// s = "level" "l"
string longestPrefix(string s) {
  int n = s.size(), j = -1;
  vector<int> next(n);
  next[0] = -1;
  for (int i = 1; i < n; i++) {
    while (j != -1 && s[j + 1] != s[i])
      j = next[j];
    if (s[j + 1] == s[i])
      j += 1;
    next[i] = j;
  }
  return s.substr(0, next[n - 1] + 1);
}

string shortestPalindrome(string s) {
  string rev_s = s;
  reverse(rev_s.begin(), rev_s.end());
  // aabc#cbaa
  rev_s = s + "#" + rev_s;

  int n = rev_s.size(), j = -1;
  vector<int> next(n);
  next[0] = -1;
  for (int i = 1; i < n; i++) {
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
int main() {
  char s1[100], s2[100];
  while (cin >> s1 >> s2) {
    TEST(brute_force, s1, s2);
  }
  return 0;
}

string getNewString(string &s) {
  string new_s = "#";
  for (int i = 0; s[i]; i++) {
    (new_s += s[i]) += "#";
  }
  return new_s;
}
// 5.   s"babad" "bab"
string longestPalindromekk(string s) {
  string ns = getNewString(s);
  vector<int> d(ns.size()); // 记录每一个位置的最长回文半径
  int l = 0, r = -1;        // 最远的r

  for (int i = 0; ns[i]; i++) {
    if (i > r) // 当前遍历的i不在任何一个回文区间
    {
      d[i] = 1;
    } else {
      d[i] = min(r - 1, d[l + r - i]);
    }
    while (i - d[i] >= 0 && ns[i - d[i]] == ns[i + d[i]]) {
      d[i]++;
    }
    if (i + d[i] > r && i - d[i] > 0) {
      l = i - d[i];
      r = i + d[i];
    }
  }
  string ret;
  int tmp = 0;
  for (int i = 0; ns[i]; i++) {
    if (tmp >= d[i])
      continue;
    tmp = d[i];
    ret = "";
    for (int j = i - d[i] + 1; j < i + d[i]; j++) {
      if (ns[j] == '#')
        continue;
      ret += ns[j];
    }
  }
  return ret;
}
int longestPalindrome(string s) {
  int char_map[128] = {0};
  int max_length = 0; // 回文串偶数部分的最大长度
  int flag = 0;       // 是否有中心点
  for (int i = 0; i < s.length(); i++) {
    char_map[s[i]]++;
  }
  for (int i = 0; i < 128; i++) {
    if (char_map[i] % 2 == 0) {
      max_length += char_map[i];
    } else {
      max_length += char_map[i] - 1;
      flag = 1;
    }
  }
  return max_length + flag; // 偶数长度+中心点字符
}
// 确认str是否与pattern匹配 pattern = "abba" str="dog cat cat dog" 匹配 pattern
// = "abba", str= "dog cat cat fish"不匹配
bool wordPattern(string pattern, string str) {
  map<string, char> word_map;
  char used[128] = {0}; // 已被映射的pattern字符
  string word;          // 临时保存拆分出的单词
  int pos = 0;          // 当前指向的pattern字符
  str.push_back(' ');   // str尾部push空格，分隔
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == ' ') {             // 遇到空格，拆出一个新单词
      if (pos == pattern.length()) { // 分隔出单词，但无pattern字符对应
        return false;
      }
      if (word_map.find(word) == word_map.end()) { // 单词没出现在映射中
        if (used[pattern[pos]]) {
          return false;
        }
        word_map[word] = pattern[pos];
        used[pattern[pos]] = 1;
      } else {
        if (word_map[word] != pattern[pos]) {
          return false;
        }
      }
      word = "";
      pos++;
    } else {
      word += str[i];
    }
  }
  if (pos != pattern.length()) {
    return false;
  }
  return true;
}
void change_to_vector(string &str, vector<int> &vec) {
  for (int i = 0; i < 26; i++) {
    vec.push_back(0);
  }
  for (int i = 0; i < str.length(); i++) {
    vec[str[i] - 'a']++;
  }
}
// 某两个字符串，出现的各个字符数相同，分一组
vector<vector<string>> groupAnagrams(vector<string> &strs) {
  map<string, vector<string>> anagram;
  vector<vector<string>> result;
  // 内部进行排序的各个单词为key 存储各个字符数量相同的字符串
  for (int i = 0; i < strs.size(); i++) {
    string str = strs[i];         // vector<int> vec;
    sort(str.begin(), str.end()); // change_to_vector(strs[i], vec);
    if (anagram.find(str) == anagram.end()) {
      vector<string> item;
      anagram[str] = item; // anagram[vec] = item;
    }
    anagram[str].push_back(strs[i]); // anagram[vec].push_back(strs[i]);
  }
  map<string, vector<string>>::iterator it;
  for (it = anagram.begin(); it != anagram.end(); it++) {
    result.push_back((*it).second);
  }
  return result;
}
// 无重复字符的最长子串长度 "abcabcbb" "abc" 3 ---子串连续
int lengthOfLongestSubstringV2(string s) {
  int begin = 0;
  int result = 0;
  // 窗口的头指针
  string word = "";
  int char_map[128] = {0};
  for (int i = 0; i < s.length(); i++) {
    char_map[s[i]]++;
    // word中没出现该字符
    if (char_map[s[i]] == 1) {
      word += s[i];
      if (result < word.length()) {
        result = word.length();
      }
    } else {
      // 重复字符是s[i]删除
      while (begin < i && char_map[s[i]] > 1) {
        char_map[s[begin]]--;
        begin++;
      }
      word = "";
      for (int j = begin; j <= i; j++) {
        word += s[j];
      }
    }
  }
  return result;
}
int g_hash_map[1048576] = {0}; // 2^20 
string change_int_to_DNA(int DNA) {
  static const char DNA_CHAR[] = {'A', 'C', 'G', 'T'};
  string str;
  for (int i = 0; i < 10; i++) { //前十个左移转换为整数key
    str += DNA_CHAR[DNA & 3];
    DNA = DNA >> 2;
  }
  return str;
}
// 
vector<string> findRepatedDnaSequencesV2(string s) {
  vector<string> result;
  if (s.length() < 10) {
    return result;
  }
  for (int i = 0; i < 1048576; i++) {
    g_hash_map[i] = 0;
  }
  int char_map[128] = {0};
  char_map['A'] = 0;
  char_map['C'] = 1;
  char_map['G'] = 2;
  char_map['T'] = 3;
  int key = 0;
  for (int i = 9; i >= 0; i--) {
    key = (key << 2) + char_map[s[i]];
  }
  g_hash_map[key] = 1;
  for (int i = 10; i < s.length(); i++) {
    key = key >> 2; //从第十一个字符开始，按顺序遍历各个字符，遇到一个字符将key右移2位（去掉最左边的2位---滑动窗口向右移动）
    key = key | (char_map[s[i]] << 18);
    g_hash_map[key]++;
  }
  for (int i = 0; i < 1048576; i++) {
    if (g_hash_map[i] > 1) {
      result.push_back(change_int_to_DNA(i));
    }
  }
  return result;
}

vector<string> findRepeatedDnaSequences(string s) {
  map<string, int> word_map;
  vector<string> result;
  for (int i = 0; i < s.length(); i++) {
    string word = s.substr(i, 10);
    if (word_map.find(word) != word_map.end()) {
      word_map[word] += 1;
    } else {
      word_map[word] = 1;
    }
  }
  map<string, int>::iterator it;
  for (it = word_map.begin(); it != word_map.end(); it++) {
    if (it->second > 1) {
      result.push_back(it->first);
    }
  }
  return result;
}
bool is_window_ok(int map_s[], int map_t[], vector<int> &vec_t) {
  for (int i = 0; i < vec_t.size(); i++) {
    if (map_s[vec_t[i]] < map_t[vec_t[i]]) {
      return false;
    }
  }
  return true;
}
string minWindow(string s, string t) {
  const int MAX_ARRAY_LEN = 128;
  // map_s当前处理的窗口区间中的字符数量， mapt_t-0-子串T的字符数量
  int map_t[MAX_ARRAY_LEN] = {0};
  int map_s[MAX_ARRAY_LEN] = {0};
  vector<int> vec_t;
  for (int i = 0; i < t.length(); i++) {
    map_t[t[i]]++;
  }
  for (int i = 0; i < MAX_ARRAY_LEN; i++) {
    if (map_t[i] > 0) {
      vec_t.push_back(i);
    }
  }
  int window_begin = 0;
  string result;
  for (int i = 0; i < s.length(); i++) { // i-窗口的尾指针
    map_s[s[i]]++;
    while (window_begin < i) { // 头要在尾巴前
      char begin_ch = s[window_begin];
      if (map_t[begin_ch] == 0) { // 指向t中没有的字符，begin直接移动
        window_begin++;
      } else if (map_s[begin_ch] > map_t[begin_ch]) {
        map_s[begin_ch]--;
        // 头指针移动了，它指向的字符-1
        window_begin++;
      } else {
        break;
      }
    }
    if (is_window_ok(map_s, map_t, vec_t)) {
      int new_window_len = i - window_begin + 1;
      if (result == "" || result.length() > new_window_len) {
        result = s.substr(window_begin, new_window_len);
      }
    }
  }
  return result;
}
int strStr(string haystack, string needle) {
  int ind[128];
  for (int i = 0; i < 128; i++)
    ind[i] = -1;
  for (int i = 0; needle[i]; i++)
    ind[needle[i]] = i;
  int i = 0;
  while (i + needle.size() <= haystack.size()) {
    int flag = 1;
    for (int j = 0; needle[j]; j++) {
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
  for (int i = 0; s[i]; i++) {
    if (cnt[s[i]] == 0)
      k += 1;
    cnt[s[i]] += 1;

    if (i >= l) // 超出窗口大小
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
int lengthOfLongestSubstring(string s) {
  if (s == "")
    return 0;
  int head = 1, tail = s.size(), mid;
  while (head < tail) {
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
string Compare(string &a, string &b) {
  string ret = "";
  for (int i = 0; a[i]; i++) {
    if (i == b.size() || a[i] != b[i])
      return ret;
    ret += a[i];
  }
  return ret;
}
string longestCommonPrefix(vector<string> &strs) {
  string ret = strs[0];
  for (int i = 1; i < strs.size(); i++) {
    ret = Compare(ret, strs[i]);
  }
  return ret;
}

// 一次编辑 f = "pale" s = "ple" output= True
bool oneEditAway(string first, string second) {
  if (first.size() < second.size())
    swap(first, second);
  int n = first.size(), m = second.size();
  if (abs(n - m) > 1)
    return false;
  if (abs(n - m) == 0) {
    for (int i = 0, j = 0; i < n; i++) {
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
