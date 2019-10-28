#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int t = 1; t <= tt; t++) {
    cout << "Case #" << t << ": ";
    int d, n;
    cin >> d >> n;
    double mm = 0;
    double a, b;
    for (int i = 0; i < n; i++) {
      cin >> a >> b;
      double r = d - a;
      r /= b;
      // cout << a << " " << b << " " << r << endl;
      mm = max(mm, r);
    }
    mm = d / mm;
    cout << fixed << setprecision(7) << mm << "\n";
  }
  return 0;
}
