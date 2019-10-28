#include <bits/stdc++.h>

using namespace std;

struct E {
  int l, r;
  E(int nl, int nr) : l(nl), r(nr) {}
  bool operator < (const E &o) const {
    int v = r - l;
    int ov = o.r - o.l;
    if (v / 2 != ov / 2) {
      return v / 2 > ov / 2;
    }
    if ((v + 1) / 2 != (ov + 1) / 2) {
      return (v + 1) / 2 > (ov + 1) / 2;
    }
    return l < o.l;
  }
};

int main() {
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
  int tt;
  scanf("%d", &tt);
  for (int cc = 1; cc <= tt; ++cc) {
    printf("Case #%d: ", cc);
    int n, k;
    scanf("%d %d", &n, &k);
    set <E> ss = {{0, n + 1}};
    while (k-- > 1) {
      int l = ss.begin()->l;
      int r = ss.begin()->r;
      ss.erase(ss.begin());
      int s = (l + r) / 2;
      if (s - l - 1 >= 1) {
        ss.emplace(l, s);
      }
      if (r - s - 1 >= 1) {
        ss.emplace(s, r);
      }
    }
    int ans = ss.begin()->r - ss.begin()->l;
    printf("%d %d\n", (ans + 1) / 2 - 1, ans / 2 - 1);
  }
}