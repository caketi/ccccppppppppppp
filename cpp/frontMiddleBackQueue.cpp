#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>


using namespace std;

void reverse(vector<int> &arr, int n, vector<int> &ind) {
  for (int i = 0, j = n - 1; i < j; i++, j--) {
    swap(arr[i], arr[j]);
    ind[arr[i]] = i;
    ind[arr[j]] = j;
  }
}
vector<int> pancakeSort(vector<int> &arr) {
  vector<int> ind(arr.size() + 1);
  vector<int> ret;
  for (int i = 0; i < arr.size(); i++)
    ind[arr[i]] = i;
  for (int i = arr.size(); i >= 1; i--) {
    if (ind[i] == i - 1)
      continue;
    if (ind[i] + 1 != 1) {
      ret.push_back(ind[i] + 1);
      reverse(arr, ind[i] + 1, ind);
    }
    if (i != 1) {
      ret.push_back(i);
      reverse(arr, i, ind);
    }
  }
  return ret;
}

bool has_repeate(string a) {
  int cnt[26] = {0};
  for (int i = 0; a[i]; i++) {
    cnt[a[i] - 'a'] += 1;
    if (cnt[a[i] - 'a'] == 2)
      return true;
  }
  return false;
}
// A == aaaaabc
// B == aaaaacb
//  找到第一个不同的字符，然后接着赵2第二个不同的字符，交叉比较，只有相等
bool buddyStrings(string a, string b) {
  if (a.size() != b.size())
    return false;
  if (a == b)
    return has_repeate(a);
  int i = 0, j;
  while (a[i] == b[i])
    ++i;     // 找到第一个不同的字符
  j = i + 1; // 找第二个不同的字符
  while (j < a.size() && a[j] == b[j])
    ++j;
  if (j == a.size())
    return false;
  if (a[i] != b[j] || a[j] != b[i])
    return false;
  j += 1; // 第三段，后面的部分也必须相等
  while (j < a.size()) {
    if (a[j] != b[j])
      return false;
    j += 1;
  }
  return true;
}

// 第k个数
int getKthMagicNumber(vector<int> &arr, int k) {
  vector<int> vec;
  arr.push_back(1);
  int p3 = 0, p5 = 0, p7 = 0;
  while (vec.size() < k) {
    int ans = 3 * arr[p3];
    ans = min(ans, 5 * vec[p5]);
    ans = min(ans, 7 * vec[p7]);
    if (3 * vec[p3] == ans)
      p3++;
    if (5 * vec[p5] == ans)
      p5++;
    if (7 * vec[p7] == ans)
      p7++;
    vec.push_back(ans);
  }
  return arr[k - 1];
}

class RecentCounter {
public:
  queue<int> q;
  RecentCounter() {}
  int ping(int t) {
    q.push(t);
    while (t - q.front() > 3000)
      q.pop();
    return q.size();
  }
};

class Node {
public:
  int val;
  Node *next, *pre;
  Node(int val = 0, Node *next = nullptr, Node *pre = nullptr)
      : val(val), next(next), pre(pre) {}
  void insert_pre(Node *p) {
    p->pre = pre;
    p->next = this;
    if (this->pre)
      this->pre->next = p;
    this->pre = p;
    return;
  }
  void insert_next(Node *p) {
    p->pre = this;
    p->next = this->next;
    if (this->next)
      this->next->pre = p;
    this->next = p;
    return;
  }
  void delete_pre() { // pre p this --- delete p
    if (this->pre == nullptr)
      return;
    Node *p = this->pre;
    this->pre = p->pre;
    if (p->pre)
      p->pre->next = this;
    delete p;
    return;
  }
  void delete_next() { // pre this p -- delete p
    if (this->next == nullptr)
      return;
    Node *p = this->next;
    this->next = p->next;
    if (p->next)
      p->next->pre = this;
    delete p;
    return;
  }
};

class Queue {
public:
  Node *head, *tail;
  int cnt;
  Queue() : cnt(0) {
    head->next = tail;
    head->pre = nullptr;
    tail->next = nullptr;
  }
  void push_back(int val) {
    tail->insert_pre(new Node(val));
    cnt += 1;
    return;
  }
  void push_front(int val) {
    head->insert_next(new Node(val));
    cnt += 1;
    return;
  }
  int front() { return head->next->val; }
  int back() { return tail->pre->val; }

  int pop_back() {
    if (isEmpty())
      return -1;
    int ret = tail->pre->val;
    tail->delete_pre();
    cnt -= 1;
    return ret;
  }
  int pop_front() {
    if (isEmpty())
      return -1;
    int ret = head->next->val;
    head->delete_next();

    cnt -= 1;
    return ret;
  }
  bool isEmpty() { return head->next == tail; }
  int size() { return cnt; }
};

class FrontMiddleBackQueue {
public:
  Queue q1, q2;
  FrontMiddleBackQueue() {}
  void pushFront(int val) {
    q1.push_front(val);
    update();
    return;
  }
  void pushMiddle(int val) {
    if (q1.size() > q2.size()) {
      q2.push_front(q1.back());
      q1.pop_back();
    }
    q1.push_back(val);
    update();
    return;
  }
  void pushback(int val) {
    q2.push_back(val);
    update();
    return;
  }
  int popFront() {
    if (isEmpty())
      return -1;
    int ret = q1.pop_front();
    update();
    return ret;
  }
  int popMiddle() {
    if (isEmpty())
      return -1;
    int ret = q1.pop_back();
    update();
    return ret;
  }
  int popBack() {
    if (isEmpty())
      return -1;
    int ret;
    if (q2.isEmpty()) {
      ret = q1.pop_back();
    } else {
      ret = q2.pop_back();
    }

    update();
    return ret;
  }

  bool isEmpty() { return q1.size() == 0; }
  void update() {
    if (q1.size() < q2.size()) {
      q1.push_back(q2.front());
      q2.pop_front();
    }
    if (q1.size() == q2.size() + 2) {
      q2.push_front(q1.back());
      q1.pop_back();
    }
    return;
  }
};

int main() {
  // Queue q();
  vector<int> v222 = {1, 3, 2, 4};

  // FrontMiddleBackQueue fmq();
  // string a = "aaaabc";
  // string b = "aaaacb";
  // bool res = buddyStrings(a, b);
  auto v = pancakeSort(v222);
  // for (int i = 0; i < v.size(); i++) cout<< v[i] << endl;
  cout << v.size() << endl;

  // cout << "" << a << " and " << b << " is buddyString? \ntrue1
  // false0\n----\n"
  //      << res << endl;
  return 0;
}