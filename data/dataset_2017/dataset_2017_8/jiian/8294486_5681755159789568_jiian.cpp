#include <bits/stdc++.h>
using namespace std;
using LL = long long;

double e[123], v[123], s[123], a[123][123], dp[123];

int main() {
  freopen("123.in", "r", stdin);
  freopen("123.out", "w", stdout);
  int T, cas = 0;
  cin >> T;
  while (T --) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i ++)
      cin >> e[i] >> v[i];
    for (int i = 1; i <= n; i ++)
      for (int j = 1; j <= n; j ++)
        cin >> a[i][j];
    for (int i = 2; i <= n; i ++)
      s[i] = s[i - 1] + a[i - 1][i];
    dp[1] = 0;
    for (int i = 2; i <= n; i ++)
      dp[i] = 1e17;
    for (int i = 0; i < n; i ++)
      for (int j = i + 1; j <= n; j ++)
        if (s[j] - s[i] <= e[i])
          dp[j] = min(dp[j], dp[i] + (s[j] - s[i]) / v[i]);
    int qu, qv;
    cin >> qu >> qv;
    printf("Case #%d: %.10f\n", ++ cas, dp[n]);
  }
  return 0;
}