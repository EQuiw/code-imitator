#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;
typedef pair<pii, ll> para;
const ll inf = 1e16 + 7;
const ll maxN = 1e3 + 5;

int n, q, u, v, t;
int horse[maxN], dist[maxN][maxN], speed[maxN];
ll pref[maxN];
ld dp[maxN];

int main() {
  ios_base::sync_with_stdio(0);
  cin >> t;
  for (ll x = (1); x <= ((t)); ++x) {
    cin >> n >> q;
    for (ll i = (1); i <= ((n)); ++i)
      cin >> horse[i] >> speed[i];
    for (ll i = (1); i <= ((n)); ++i) {
      for (ll j = (1); j <= ((n)); ++j) {
        cin >> dist[i][j];
      }
    }
    pref[1] = 0;
    for (ll i = (2); i <= (n); ++i) {
      pref[i] = pref[i - 1] + dist[i - 1][i];
    }
    cout << "Case #" << x << ": ";
    for (ll _ = (0); _ <= ((q)-1); ++_) {
      cin >> u >> v;
      for (ll i = (1); i <= ((n)); ++i)
        dp[i] = (ld)inf;
      dp[1] = 0;
      for (ll i = (1); i <= ((n)); ++i) {
        for (ll j = (i + 1); j <= (n); ++j) {
          // cout<<i<<" "<<j<<" "<<dist<<endl;
          if (pref[j] - pref[i] > horse[i])
            break;
          dp[j] = min(dp[j], dp[i] + (pref[j] - pref[i]) / (ld)speed[i]);
        }
      }
      cout << fixed << setprecision(9) << dp[n];
    }
    cout << endl;
  }
  return 0;
}
