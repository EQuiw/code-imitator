#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;
int n, m, flag, tot;
int t[101], s[101][101], cnt[51];
struct data {
  int a, l, r;
  data() {}
  data(int a, int l, int r) : a(a), l(l), r(r) {}
  bool operator<(const data &x) const { return r > x.r; }
} g[1010];
bool cmp(const data &x, const data &y) { return x.l < y.l; }
priority_queue<data> que[101];
int main() {
  // freopen("input.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
  int T, ans;
  cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    cin >> n >> m;
    tot = ans = 0;
    for (int i = 1; i <= n; ++i)
      while (!que[i].empty())
        que[i].pop();
    for (int i = 1; i <= n; ++i)
      scanf("%d", &t[i]);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        scanf("%d", &s[i][j]);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        if (s[i][j]) {
          int r = floor((double)s[i][j] / (0.9 * t[i]));
          int l = ceil((double)s[i][j] / (1.1 * t[i]));
          if (l == 0)
            l = 1;
          if (l <= r)
            g[++tot] = data(i, l, r);
          // printf("s = %d l = %d r = %d\n", s[i][j], l, r);
        }
    sort(g + 1, g + tot + 1, cmp);
    for (int i = 1; i <= tot; ++i) {
      // printf("g[%d] = (%d %d %d)\n", g[i].a, g[i].l, g[i].r);
      for (int j = 1; j <= n; ++j)
        while (!que[j].empty() && que[j].top().r < g[i].l)
          que[j].pop();
      que[g[i].a].push(g[i]);
      int minvalue = 1 << 29;
      for (int j = 1; j <= n; ++j)
        if (que[j].size() < minvalue)
          minvalue = que[j].size();
      ans += minvalue;
      for (int j = 1; j <= n; ++j)
        for (int k = 1; k <= minvalue; ++k)
          que[j].pop();
    }
    printf("Case #%d: %d\n", cas, ans);
  }
  return 0;
}
