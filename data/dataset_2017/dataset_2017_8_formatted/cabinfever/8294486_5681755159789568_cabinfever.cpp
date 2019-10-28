#include <bits/stdc++.h>

using namespace std;

int T, n, q;
double haha[110][110];
double f[110];
double sum[110];
double e[110], s[110];
int v, u;
double ans[110];

int main() {
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
  cin >> T;
  for (int ii = 1; ii <= T; ii++) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
      scanf("%lf%lf", &e[i], &s[i]);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        scanf("%lf", &haha[i][j]);
    for (int i = 2; i <= n; i++)
      sum[i] = sum[i - 1] + haha[i - 1][i];
    for (int iii = 1; iii <= q; iii++) {
      scanf("%d%d", &u, &v);
      for (int i = 2; i <= n; i++) {
        f[i] = 1e12;
        for (int j = 1; j < i; j++) {
          if (sum[i] - sum[j] > e[j])
            continue;
          f[i] = min(f[j] + (sum[i] - sum[j]) / s[j], f[i]);
        }
      }
      ans[iii] = f[n];
    }
    printf("Case #%d: ", ii);
    for (int i = 1; i <= q; i++)
      printf("%.8lf%c", ans[i], i == q ? '\n' : ' ');
  }
  return 0;
}
