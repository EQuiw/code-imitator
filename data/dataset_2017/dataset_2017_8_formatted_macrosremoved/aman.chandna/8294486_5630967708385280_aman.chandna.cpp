

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
  double t;
  cin >> t;
  cout << std::fixed;
  for (long long ccr = 1; ccr <= t; ++ccr) {
    double d, n, ans = INT_MIN;
    cin >> d >> n;
    for (double i = 0; i < n; ++i) {
      double k, s;
      cin >> k >> s;
      k = d - k;
      double tme = k / s;
      ans = max(ans, tme);
    }
    ans = d / ans;
    cout << "Case #" << ccr << ": " << setprecision(7) << ans << "\n";
  }

  return 0;
}
