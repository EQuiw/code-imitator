#include <bits/stdc++.h>

int main() {
  int tc;
  scanf("%d", &tc);
  int P = 0;
  while (tc--) {
    long long d, n;
    scanf("%lld%lld", &d, &n);
    double ans = 0;
    for (int i = 0; i < n; i++) {
      long long k, s;
      scanf("%lld%lld", &k, &s);
      double t = ((double)(d - k)) / s;
      if (i == 0) {
        ans = d / t;
      } else {
        ans = std::min(ans, d / t);
      }
    }
    P++;
    printf("Case #%d: %.6lf\n", P, ans);
  }
}
