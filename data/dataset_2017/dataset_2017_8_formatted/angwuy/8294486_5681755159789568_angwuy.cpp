#include <cstdio>
#include <cstring>

const int MAXN = 110;
const long long INF = 10000000000000000LL;

int n, q;
long long e[MAXN], s[MAXN];
long long d[MAXN][MAXN];
double ans[MAXN][MAXN];

long long min(long long x, long long y) { return x < y ?: y; }

void init() {
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%I64d %I64d", &e[i], &s[i]);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      scanf("%I64d", &d[i][j]);
      if (d[i][j] < 0)
        d[i][j] = INF;
    }
}

void solve() {
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      if (i != j)
        ans[i][j] = (double)INF;
      else
        ans[i][j] = 0;
    }

  for (int k = 1; k <= n; ++k)
    for (int l = 1; l <= n; ++l) {
      if (d[k][l] > e[k])
        continue;
      double tmp = (double)d[k][l] / (double)s[k];
      for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
          double tmp2 = ans[i][k] + ans[l][j] + tmp;
          if (tmp2 < ans[i][j])
            ans[i][j] = tmp2;
        }
    }
  for (int i = 1; i <= q; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    printf(" %.8lf", ans[x][y]);
  }
  printf("\n");
}

int main() {
  int tt;
  scanf("%d", &tt);
  for (int ii = 1; ii <= tt; ++ii) {
    init();
    printf("Case #%d:", ii);
    solve();
  }
  return 0;
}