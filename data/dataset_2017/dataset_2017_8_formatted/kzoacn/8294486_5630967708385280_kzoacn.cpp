#include <bits/stdc++.h>
using namespace std;

double solve() {
  double d;
  int n;
  scanf("%lf%d", &d, &n);
  double mxt = 0;
  for (int i = 1; i <= n; i++) {
    double k, s;
    scanf("%lf%lf", &k, &s);
    double t = (d - k) / s;
    mxt = max(mxt, t);
  }
  return d / mxt;
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    printf("Case #%d: %.10f\n", t, solve());
  }
  return 0;
}
