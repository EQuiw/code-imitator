#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 50 + 5;
int T, Case, n, k;
double u, p[N];

bool ok(double t, double u) {
  for (int i = 1; i <= n; i++) {
    if (p[i] < t)
      u -= t - p[i];
  }
  return u >= 0;
}

double get(double t) {
  double ret = 1;
  for (int i = 1; i <= n; i++) {
    ret *= max(p[i], t);
  }
  return ret;
}

int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("out0.out", "w", stdout);
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    scanf("%lf", &u);
    for (int i = 1; i <= n; i++) {
      scanf("%lf", &p[i]);
    }
    double l = *min_element(p + 1, p + n + 1), r = 1;
    for (int i = 0; i < 100; i++) {
      double m = (l + r) / 2.0;
      if (ok(m, u))
        l = m;
      else
        r = m;
    }
    printf("Case #%d: %.6f\n", ++Case, get(l));
  }
  return 0;
}
