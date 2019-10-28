#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int t = 1; t <= tt; t++) {
    cout << "Case #" << t << ": ";
    int n, q;
    cin >> n >> q;
    assert(q == 1);
    int e[n], s[n];
    for (int i = 0; i < n; i++)
      cin >> e[i] >> s[i];
    int g[n][n];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        cin >> g[i][j];
    }
    int d[n];
    d[0] = 0;
    double f[n];
    f[0] = 0;
    for (int i = 1; i < n; i++)
      f[i] = f[i - 1] + g[i - 1][i];
    double r[n];
    r[0] = 0;
    int x, y;
    cin >> x >> y;
    for (int i = 1; i < n; i++) {
      r[i] = 1e12;
      for (int j = 0; j < i; j++) {
        if (f[i] - f[j] <= e[j]) {
          r[i] = min(r[i], r[j] + (0.0 + f[i] - f[j]) / (1.0 * s[j]));
        }
        //	cout << i << " " << j << " " << r[i] << endl;
      }
    }
    cout << fixed << setprecision(7) << r[n - 1] << endl;
  }
  return 0;
}
