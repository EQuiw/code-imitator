#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int tt;
  cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> ar(n);
    for (int i = 0; i < n; ++i) {
      cin >> ar[i].first >> ar[i].second;
    }
    vector<vector<int>> d(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cin >> d[i][j];
      }
    }
    int start, finish;
    cin >> start >> finish;
    start--;
    finish--;
    vector<double> dp(n, 1e+12);
    dp[0] = 0;
    for (int i = 0; i < n - 1; ++i) {
      long long int dd = d[i][i + 1];
      int j = i + 1;
      while (dd <= ar[i].first) {
        dp[j] = min(dp[j], dp[i] + dd / double(ar[i].second));
        if (j == n - 1)
          break;
        else {
          dd += d[j][j + 1];
          j++;
        }
      }
    }
    cout << "Case #" << t << ": " << fixed << setprecision(20) << dp[n - 1]
         << endl;
  }
}