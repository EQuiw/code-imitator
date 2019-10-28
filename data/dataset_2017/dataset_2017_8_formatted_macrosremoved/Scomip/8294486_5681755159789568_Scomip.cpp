#include <bits/stdc++.h>

using namespace std;

int n, q;
struct horse {
  int e, s;
} h[110];
int a[110][110];

void solve() {
  cin >> n >> q;
  for (int i = 0; i < n; i++)
    cin >> h[i].e >> h[i].s;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> a[i][j];
  cin >> q >> q;

  vector<pair<horse, double>> x, y;
  x.push_back({h[0], 0});
  for (int i = 1; i < n; i++) {
    y.clear();
    double best = 1e18;
    for (auto p : x) {
      if (p.first.e >= a[i - 1][i]) {
        double d = p.second + (double)a[i - 1][i] / p.first.s;
        y.push_back({{p.first.e - a[i - 1][i], p.first.s}, d});
        best = min(best, d);
      }
    }
    y.push_back({h[i], best});
    x = y;
  }
  double ans = 1e18;
  for (auto p : x)
    ans = min(ans, p.second);
  cout << setprecision(20) << ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    solve();
    cout << endl;
  }

  return 0;
}
