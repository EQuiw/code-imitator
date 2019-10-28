

#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int main() {

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  freopen("inp3.txt", "r", stdin);
  freopen("out3.txt", "w", stdout);
  long long t;
  cin >> t;
  cout << std::fixed;
  for (long long ccr = 1; ccr <= t; ++ccr) {
    double n, q;
    cin >> n >> q;
    pair<double, double> in;
    vector<pair<double, double>> hinfo(n, in);
    for (double i = 0; i < n; ++i)
      cin >> hinfo[i].first >> hinfo[i].second;
    vector<vector<double>> graph(n, vector<double>(n, 0));
    for (double i = 0; i < n; ++i) {
      for (double j = 0; j < n; ++j) {
        cin >> graph[i][j];
      }
    }
    vector<double> ans(n, 0.0);
    for (double i = n - 2; i >= 0; --i) {
      double opt = DBL_MAX;
      double dist = 0.0;
      for (double j = i + 1; j < n; ++j) {
        dist += graph[j - 1][j];
        if (dist <= hinfo[i].first) {
          opt = min(opt, dist / hinfo[i].second + ans[j]);
        } else {
          break;
        }
      }
      ans[i] = opt;
    }
    for (double i = 0; i < q; ++i) {
      double aa;
      cin >> aa >> aa;
    }
    cout << "Case #" << ccr << ": " << setprecision(7) << ans[0] << "\n";
  }
  return 0;
}
