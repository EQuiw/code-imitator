

#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int main() {

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  freopen("inp1.txt", "r", stdin);
  freopen("out1.txt", "w", stdout);
  long double t;
  cin >> t;
  cout << std::fixed;
  for (long long ccr = 1; ccr <= t; ++ccr) {
    long double n, k, ans = DBL_MIN;
    cin >> n >> k;
    vector<pair<long double, long double>> vec(n, {0.0, 0.0});
    for (long double i = 0; i < n; ++i)
      cin >> vec[i].second >> vec[i].first;
    long double pi = 3.14159265358979323846;
    for (long double i = 0; i < n; ++i) {
      long double rad = vec[i].second, ht = vec[i].first;
      long double opt = pi * rad * rad + 2 * pi * rad * ht;
      priority_queue<long double, vector<long double>, greater<long double>> pq;
      for (long double j = 0; j < n; ++j) {
        if (j == i)
          continue;
        if (vec[j].second <= vec[i].second) {
          long double val = 2 * pi * vec[j].first * vec[j].second;
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
