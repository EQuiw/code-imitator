#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[20][10][2]; // [N][last][se]

void solve() {
  ll N;
  cin >> N;

  memset(dp, -1, sizeof dp);

  string s = to_string(N);
  reverse(s.begin(), s.end());

  int n = s.size();
  dp[0][9][1] = 0;
  ll cur = 0;
  for (int i = 0; i < n; i++) {
    cur += (ll)pow(10, i) * (s[i] - '0');
    // cerr << cur << endl;
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 2; k++) {
        if (dp[i][j][k] == -1)
          continue;
        ll d = dp[i][j][k];
        for (int l = 0; l <= j; l++) {
          ll nd = d + (ll)pow(10, i) * l;
          int nse = nd <= cur;
          dp[i + 1][l][nse] = max(dp[i + 1][l][nse], nd);
        }
      }
    }
  }
  ll ans = 0;
  for (int i = 0; i < 10; i++) {
    ans = max(ans, dp[n][i][1]);
  }
  cout << ans << endl;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cout << "Case #" << i + 1 << ": ";
    solve();
  }
}
