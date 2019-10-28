#include <bits/stdc++.h>

const int N = 1000;
typedef long long ll;

using namespace std;

double dp[N];
ll sum[N], f[N], d[N][N];
int q, n;
ll w[N], s[N];

void solve() {
  for (int i = 1; i <= n; i++)
    dp[i] = 1000000000000009;
  f[1] = 0;
  for (int i = 2; i <= n; i++)
    f[i] = f[i - 1] + d[i - 1][i];
  dp[1] = 0.0;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      int sum = f[j] - f[i];
      if (sum > w[i])
        break;
      dp[j] = min(dp[j], dp[i] + (double)sum / (double)s[i]);
    }
  }
}

int main() {
  int query;
  scanf("%d", &query);
  for (int t = 1; t <= query; t++) {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
      scanf("%d %d", &w[i], &s[i]);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        scanf("%d", &d[i][j]);
    int u, v;
    for (int i = 1; i <= q; i++) {
      scanf("%d %d", &u, &v);
      solve();
    }
    printf("Case #%d: %0.9lf\n", t, dp[n]);
  }
}
