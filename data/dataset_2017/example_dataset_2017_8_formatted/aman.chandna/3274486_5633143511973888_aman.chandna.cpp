#define boost                                                                  \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);
#define mod 1000000007
#define INF LLONG_MAX
#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define ll double
#define lpair pair<double, double>
int main() {

  boost;
  freopen("inp3.txt", "r", stdin);
  freopen("out3.txt", "w", stdout);
  long long t;
  cin >> t;
  cout << std::fixed;
  for (long long ccr = 1; ccr <= t; ++ccr) {
    ll n, u, k, tot = 0, ans = 1.0;
    cin >> n >> k;
    cin >> u;
    vector<ll> prob(n, 0.0);
    for (ll i = 0; i < n; ++i) {
      cin >> prob[i];
      tot += prob[i];
    }
    ll newTot = tot + u;
    if (newTot >= k) {
      ans = 1.0;
    } else {
      sort(prob.begin(), prob.end());
      ll each = newTot / n;
      for (ll i = n - 1; i >= 0; --i) {
        if (each < prob[i]) {
          ans *= prob[i];
          newTot -= prob[i];
          if (i != 0)
            each = newTot / (i);
        } else {
          ans *= pow(each, i + 1);
          break;
        }
      }
    }
    cout << "Case #" << ccr << ": " << setprecision(8) << ans << "\n";
  }
  return 0;
}