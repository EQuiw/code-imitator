#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const int MAXN = 1 * 1000 + 10;
const double PI = acos(-1);

ll dp[MAXN][MAXN];
pll c[MAXN];

int main() {
  ios::sync_with_stdio(false);

  int tt;
  cin >> tt;
  for (int tc = 1; tc <= tt; tc++) {
    cout << "Case #" << tc << ": ";
    memset(dp, 0, sizeof dp);

    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
      cin >> c[i].first >> c[i].second;
    sort(c, c + n);

    for (int j = 1; j <= k; j++) {
      ll cur = 0;
      for (int i = 0; i < n; i++) {
        ll base = 2 * c[i].first * c[i].second;
        dp[i][j] = cur + base;
        cur = max(cur, dp[i][j - 1]);
      }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++)
      ans = max(ans, dp[i][k] + ((c[i].first) * (c[i].first)));
    cout << fixed << setprecision(6) << ans * PI << endl;
  }
  return 0;
}
