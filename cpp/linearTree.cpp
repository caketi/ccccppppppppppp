// 每个节点维护一个区间(l,r)并维护一个当前区间和sum
#include <iostream>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
int a[maxn], n, m;
struct node {
  int l, r; // a[l.....r]
  ll sum;
} ch[maxn << 2]; // a[1....n]--4n
inline int lson(int x) { return x << 1; }
inline int rson(int x) {
  return x << 1 | 1; // 2x+1
}
void build(int x, int l, int r) {
  ch[x].l = l;
  ch[x].r = r;
  if (l == r) {
    ch[x].sum = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(lson(x), l, mid);
  build(rson(x), mid + 1, r);
  ch[x].sum = ch[lson(x)].sum + ch[rson(x)].sum;
}
void update(int x, int pos, int v) {
  if (ch[x].l == ch[x].r) {
    ch[x].sum += v;
    return;
  }
  int mid = (ch[x].l + ch[x].r) >> 1;
  if (pos <= mid) {
    update(lson(x), pos, v);
  } else {
    update(rson(x), pos, v);
  }
  ch[x].sum = ch[lson(x)].sum + ch[rson(x)].sum;
}
ll query(int x, int ql, int qr) {
  if (ql <= ch[x].l && qr >= ch[x].r) {
    return ch[x].sum;
  }
  int mid = (ch[x].l + ch[x].r) >> 1;
  ll s = 0;
  if (ql <= mid) {
    s += query(lson(x), ql, qr);
  }
  if (qr >= mid + 1) {
    s += query(rson(x), ql, qr);
  }
  return s;
}
int main() {

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  build(1, 1, n);
  return 0;
}