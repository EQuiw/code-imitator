#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int a[1020][1020];

int e[1020], s[1020];

long long int dp[1020][1020];
long double _ist[1020][1020];
long double res[1020][1020];
long double act[1020][1020];
long double en[1020], sp[1020];
void solve(int ind) {
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> e[i] >> s[i];
    en[i] = (long double)e[i];
    sp[i] = (long double)s[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      cin >> a[i][j];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i != j) {
        dp[i][j] = a[i][j];
        if (dp[i][j] == -1)
          dp[i][j] = 100000000000000LL;
      } else
        dp[i][j] = 0;
    }
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      _ist[i][j] = (long double)dp[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (_ist[i][j] > e[i])
        res[i][j] = (long double)100000000000000LL;
      else
        res[i][j] = _ist[i][j] / sp[i];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      act[i][j] = res[i][j];
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
        act[i][j] = min(act[i][j], act[i][k] + act[k][j]);
    }
  }
  cout << "Case #" << ind << ": ";
  for (int i = 1; i <= q; i++) {
    int u, v;
    cin >> u >> v;
    printf("%.6f ", (double)act[u][v]);
  }
  printf("\n");
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++)
    solve(i);
  return 0;
}
