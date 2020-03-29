#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int tt;
  cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    int n, k;
    cin >> n >> k;
    double mx = 0;
    vector<long long int> r(n);
    vector<long long int> h(n);
    for (int i = 0; i < n; ++i) {
      cin >> r[i] >> h[i];
    }
    for (int i = 0; i < n; ++i) {
      vector<double> ar(n - 1);
      int cur = 0;
      for (int j = 0; j < n; ++j) {
        if (i == j)
          continue;
        ar[cur++] = -2 * M_PI * r[j] * h[j];
      }
      sort(ar.begin(), ar.end());
      double sum = M_PI * (2 * r[i] * h[i] + r[i] * r[i]);
      for (int j = 0; j < k - 1; ++j) {
        sum -= ar[j];
      }
      mx = max(mx, sum);
    }
    cout << "Case #" << t << ": " << fixed << setprecision(20) << mx << endl;
  }
}
