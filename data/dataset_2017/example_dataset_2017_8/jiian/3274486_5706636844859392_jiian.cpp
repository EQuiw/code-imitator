#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using pii = pair <int, int>;

struct node {
  int l, r, i;
  node() {}
  node(int l, int r, int i) : l(l), r(r), i(i) {}
  bool operator < (const node & a) const {
    return l == a.l ? r < a.r : l < a.l;
  }
};


int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("123.out", "w", stdout);
  int t, cas = 0;
  cin >> t;
  int len = 24 * 60 / 2;
  while (t --) {
    int n, m;
    int len0 = 0, len1 = 0, relax = 0;
    cin >> n >> m;
    vector <node> v;
    while (n --) {
      int l, r;
      cin >> l >> r;
      len0 += r - l;
      v.emplace_back(l, r, 0);
    }
    while (m --) {
      int l, r;
      cin >> l >> r;
      len1 += r - l;
      v.emplace_back(l, r, 1);
    }
    sort(v.begin(), v.end());
    v.emplace_back(v[0].l + 1440, v[0].l + 1440, v[0].i);
    int ans[2] = {0, 0}, add = 0;
    multiset <int> s[2], side;
    for (int i = 1; i < v.size(); i ++) {
      if (v[i].i != v[i - 1].i) {
        add ++;
        relax += v[i].l - v[i - 1].r;
      } else {
        s[v[i].i].insert(v[i].l - v[i - 1].r);
      }
    }
    int res = len - len0;
    for (auto x : s[0]) {
      if (x <= res) res -= x;
      else {
        ans[0] += 2;
        relax += x;
      }
    }
    res = len - len1;
    for (auto x : s[1]) {
      if (x <= res) res -= x;
      else {
        ans[1] += 2;
        relax += x;
      }
    }
    printf("Case #%d: %d\n", ++ cas, max(ans[0], ans[1]) + add);
  }
  return 0;
}