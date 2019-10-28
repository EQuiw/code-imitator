#include <bits/stdc++.h>

using namespace std;

int T, n;
double s[1010], d, k[1010], t, p;
struct node {
  double s, k;
  bool operator<(const node &b) const { return k < b.k; }
} a[1010];

int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  cin >> T;
  for (int ii = 1; ii <= T; ii++) {
    cin >> d >> n;
    t = 0;
    for (int i = 1; i <= n; i++)
      scanf("%lf%lf", &a[i].k, &a[i].s);
    sort(a + 1, a + 1 + n);
    p = a[1].k;
    int i;
    for (i = 1; i < n; i++) {
      if (a[i].s < a[i + 1].s)
        break;
      double tt = (a[i + 1].k + a[i + 1].s * t - p) / (a[i].s - a[i + 1].s);
      double pp = p + tt * a[i].s;
      if (pp > d) {
        break;
      } else {
        p = pp;
        t += tt;
      }
    }
    t += (d - p) / a[i].s;
    printf("Case #%d: ", ii);
    printf("%.6lf\n", d / t);
  }
  return 0;
}
