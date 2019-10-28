#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  cin >> t;
  for (int I = 1; I <= t; I++) {
    int d, n, k, s;
    printf("Case #%d: ", I);
    cin >> d >> n;
    double time = -1;
    for (int i = 1; i <= n; i++) {
      cin >> k >> s;
      time = max(time, 1.0 * (d - k) / s);
    }
    printf("%.6lf\n", d / time);
  }
  return 0;
}
