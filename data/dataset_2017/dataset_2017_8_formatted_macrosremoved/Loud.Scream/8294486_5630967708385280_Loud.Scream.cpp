#include <bits/stdc++.h>

using namespace std;
const double EPS = 1e-9;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  cout << fixed << setprecision(7);
  for (int qq = 1; qq <= t; ++qq) {
    cout << "Case #" << qq << ": ";
    int n;
    long double d;
    cin >> d >> n;
    long double st[n], v[n];
    for (int i = 0; i < n; ++i)
      cin >> st[i] >> v[i];
    long double mx = -1.0;
    for (int i = 0; i < n; ++i)
      mx = max(mx, (d - st[i]) / v[i]);
    long double l = d / mx;
    cout << l << "\n";
  }
  return 0;
}
