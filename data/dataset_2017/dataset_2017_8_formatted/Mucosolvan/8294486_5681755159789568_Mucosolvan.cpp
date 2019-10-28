#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (ll i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (ll i = (a); i >= (b); --i)
#define RI(i, n) FOR(i, 1, (n))
#define REP(i, n) FOR(i, 0, (n)-1)
#define mini(a, b) a = min(a, b)
#define maxi(a, b) a = max(a, b)
#define mp make_pair
#define pb push_back
#define st first
#define nd second
#define sz(w) (ll) w.size()
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
  RI(x, t) {
    cin >> n >> q;
    RI(i, n)
    cin >> horse[i] >> speed[i];
    RI(i, n) {
      RI(j, n) { cin >> dist[i][j]; }
    }
    pref[1] = 0;
    FOR(i, 2, n) { pref[i] = pref[i - 1] + dist[i - 1][i]; }
    cout << "Case #" << x << ": ";
    REP(_, q) {
      cin >> u >> v;
      RI(i, n) dp[i] = (ld)inf;
      dp[1] = 0;
      RI(i, n) {
        FOR(j, i + 1, n) {
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
