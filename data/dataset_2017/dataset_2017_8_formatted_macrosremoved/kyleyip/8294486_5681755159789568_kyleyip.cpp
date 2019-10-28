#include <cstdio>
using namespace std;
int test, sum[110], d[110][110], e[110], n, q, i, j, u, v;
double s[110], f[110][110];
double min(double a, double b) { return a < b ? a : b; }
int main() {
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
  scanf("%d", &test);
  for (int kase = 1; kase <= test; kase++) {
    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; i++)
      scanf("%d%lf", &e[i], &s[i]);
    for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
        scanf("%d", &d[i][j]);
    scanf("%d%d", &u, &v); // 1->n
    sum[1] = 0;
    for (i = 2; i <= n; i++)
      sum[i] = sum[i - 1] + d[i - 1][i];
    for (i = 2; i <= n; i++)
      for (j = 1; j < i; j++)
        f[i][j] = -1;
    f[2][1] = (double)d[1][2] / s[1];
    for (i = 2; i < n; i++)   // current postion
      for (j = 1; j < i; j++) // which horse before
      {
        // switch to a new horse ?
        // continue use the horse£¿
        if (f[i][j] < 0)
          continue;
        double cur1 = -1, cur2 = -1;
        if (e[j] >= sum[i + 1] - sum[j])
          cur1 = f[i][j] + (double)d[i][i + 1] / s[j];
        if (e[i] >= d[i][i + 1])
          cur2 = f[i][j] + (double)d[i][i + 1] / s[i];
        if (cur1 < 0 && cur2 < 0)
          continue;
        if (cur1 > 0) {
          if (f[i + 1][j] < 0)
            f[i + 1][j] = cur1;
          else
            f[i + 1][j] = min(f[i + 1][j], cur1);
        }
        if (cur2 > 0) {
          if (f[i + 1][i] < 0)
            f[i + 1][i] = cur2;
          else
            f[i + 1][i] = min(f[i + 1][i], cur2);
        }
      }
    double ans = -1;
    for (i = 1; i < n; i++) {
      if (f[n][i] < 0)
        continue;
      if (ans < 0)
        ans = f[n][i];
      else
        ans = min(ans, f[n][i]);
    }
    printf("Case #%d: %.8lf\n", kase, ans);
  }
  fclose(stdin);
  fclose(stdout);
}
