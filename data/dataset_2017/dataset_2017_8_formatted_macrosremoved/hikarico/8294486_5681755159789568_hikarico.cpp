#include <bits/stdc++.h>
using namespace std;
const int N = 105;

int t, tc, n;
int q, e[N], s[N], u, v, d[N][N];
double dp[N];

int main() {
  cout.precision(10);
  cout << fixed;
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    cout << "Case #" << ++tc << ": ";
    // small
    cin >> q;
    for (int i = 1; i <= n; ++i)
      cin >> e[i] >> s[i];
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        cin >> d[i][j];
    cin >> u >> v;
    fill(dp, dp + n + 1, HUGE_VAL);
    dp[1] = 0;
    for (int i = 1; i <= n; ++i) {
      long long dist = 0;
      for (int j = i + 1; j <= n; ++j) {
        dist += d[j - 1][j];
        if (dist <= e[i]) {
          // horse can go here
          dp[j] = min(dp[j], dp[i] + 1.0 * dist / s[i]);
        }
      }
    }
    cout << dp[n] << '\n';
  }
}
