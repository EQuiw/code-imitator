

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
    double n, u, k, tot = 0, ans = 1.0;
    cin >> n >> k;
    cin >> u;
    vector<double> prob(n, 0.0);
    for (double i = 0; i < n; ++i) {
      cin >> prob[i];
      tot += prob[i];
    }
    double newTot = tot + u;
    if (newTot >= k) {
      ans = 1.0;
    } else {
      sort(prob.begin(), prob.end());
      double each = newTot / n;
      for (double i = n - 1; i >= 0; --i) {
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
