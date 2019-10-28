/*
 * Author: Vladislav Belov
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

void solution();

int main() {
  ios::sync_with_stdio(false);

  solution();

  return EXIT_SUCCESS;
}

typedef long long ll;

ll n, q, e[128], s[128], g[128][128];
ll from[128], to[128];

double dp[128];

void solve() {
  for (ll i = 0; i < n; ++i)
    dp[i] = 1e18;
  dp[0] = 0;
  for (ll i = 0; i < n; ++i) {
    double d = 0;
    for (ll j = i + 1; j < n; ++j) {
      d += g[j - 1][j];
      if (fabs(d - e[i]) < 1e-9 || d < e[i]) {
        dp[j] = min(dp[j], dp[i] + d / s[i]);
      } else {
        break;
      }
    }
  }
  cout << setprecision(9) << fixed << dp[n - 1];
}

void solution() {
  ll T;
  cin >> T;
  for (ll t = 0; t < T; ++t) {
    cerr << t + 1 << endl;
    cout << "Case #" << t + 1 << ": ";
    cin >> n >> q;
    for (ll i = 0; i < n; ++i)
      cin >> e[i] >> s[i];
    for (ll i = 0; i < n; ++i)
      for (ll j = 0; j < n; ++j)
        cin >> g[i][j];
    for (ll i = 0; i < q; ++i) {
      cin >> from[i] >> to[i];
      --from[i];
      --to[i];
    }
    solve();
    cout << '\n';
  }
}
