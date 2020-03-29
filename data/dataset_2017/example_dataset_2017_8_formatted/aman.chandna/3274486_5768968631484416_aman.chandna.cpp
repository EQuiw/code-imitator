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
#define ll long double

int main() {

  boost;
  freopen("inp1.txt", "r", stdin);
  freopen("out1.txt", "w", stdout);
  ll t;
  cin >> t;
  cout << std::fixed;
  for (long long ccr = 1; ccr <= t; ++ccr) {
    ll n, k, ans = DBL_MIN;
    cin >> n >> k;
    vector<pair<ll, ll>> vec(n, {0.0, 0.0});
    for (ll i = 0; i < n; ++i)
      cin >> vec[i].second >> vec[i].first;
    ll pi = 3.14159265358979323846;
    for (ll i = 0; i < n; ++i) {
      ll rad = vec[i].second, ht = vec[i].first;
      ll opt = pi * rad * rad + 2 * pi * rad * ht;
      priority_queue<ll, vector<ll>, greater<ll>> pq;
      for (ll j = 0; j < n; ++j) {
        if (j == i)
          continue;
        if (vec[j].second <= vec[i].second) {
          ll val = 2 * pi * vec[j].first * vec[j].second;
          if (pq.size() < k - 1 || (k > 1 && pq.top() < val)) {
            if (pq.size() == k - 1)
              pq.pop();
            pq.push(val);
          }
        }
      }
      if (pq.size() == k - 1) {
        while (!pq.empty()) {
          opt += pq.top();
          pq.pop();
        }
        ans = max(ans, opt);
      }
    }

    cout << "Case #" << ccr << ": " << setprecision(8) << ans << "\n";
  }

  return 0;
}