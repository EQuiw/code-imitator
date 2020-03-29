
/*
Contest: Google Code Jam 2017 [Round 1C]
*/

#include <algorithm>
#include <stdio.h>
using namespace std;

int n, k;
double u;
double p[55];

bool check(double l) {
  // printf("Check (%.9f)\n",l);
  double req = 0.0;
  for (int i = 0; i < n; i++) {
    if (p[i] >= l)
      continue;
    req += l - p[i];
    if (req > u)
      return false;
  }
  // printf("Required: %.9f\n",req);
  return true;
}

double eps = 0.000000000000001;
double getMe(double l, double r) {
  double md = (l + r) / 2;
  if (r - l <= eps)
    return md;
  if (check(md))
    return getMe(md, r);
  else
    return getMe(l, md);
}

double solve() {
  scanf("%d%d", &n, &k);
  scanf("%lf", &u);
  for (int i = 0; i < n; i++)
    scanf("%lf", &p[i]);
  double base = getMe(0.0000, 1.00000);
  // printf("BASE = %.9f\n",base);
  double prd = 1.0;
  for (int i = 0; i < n; i++) {
    double thisOne = max(p[i], base);
    prd *= thisOne;
  }
  return prd;
}

int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("C-Small1.txt", "w", stdout);
  int tc;
  scanf("%d", &tc);
  for (int t = 1; t <= tc; t++) {
    printf("Case #%d: ", t);
    double ans = solve();
    printf("%.9f\n", ans);
  }
  return 0;
}
