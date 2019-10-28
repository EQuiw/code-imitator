#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

double f[111], sum[111], e[111], s[111], edge[111][111];
int n, q;

void solve(int u, int t) {
  memset(f, 0, sizeof(f));
  memset(sum, 0, sizeof(sum));
  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + edge[i - 1][i];
    // printf("%lf\n", sum[i]);
  }
  f[1] = 0;
  for (int i = 2; i <= n; ++i) {
    f[i] = 1e20;
    for (int j = 1; j < i; ++j) {
      if (e[j] >= (sum[i] - sum[j])) {
        // printf("i = %d j=%d\n", i, j);
        // printf("%lf\n", (sum[i]-sum[j-1])/s[j]);
        f[i] = min(f[i], f[j] + (sum[i] - sum[j]) / s[j]);
      }
    }
  }
  printf("%lf", f[n]);
}

void work() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%lf%lf", &e[i], &s[i]);
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      scanf("%lf", &edge[i][j]);
    }
  }
  while (q--) {
    int u, t;
    scanf("%d%d", &u, &t);
    solve(u, t);
    if (q == 0)
      printf("\n");
    else
      printf(" ");
  }
}

int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-small-attempt0.out", "w", stdout);
  int TC;
  scanf("%d", &TC);
  for (int tc = 1; tc <= TC; ++tc) {
    printf("Case #%d: ", tc);
    work();
  }
}
