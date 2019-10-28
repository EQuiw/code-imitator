#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

int n, p, b[10], a[10][20], c[20];
int ans;

void calc() {
  int ret = 0;
  double xl = b[0] * 0.9, xr = b[0] * 1.1;
  double yl = b[1] * 0.9, yr = b[1] * 1.1;
  // printf("%lf %lf\n", xl, xr);
  for (int i = 0; i < p; ++i) {
    double x = a[0][i], y = a[1][c[i]];
    int xll = (int)(x / xl);
    int xrr = (int)round(x / xr);
    int yll = (int)(y / yl);
    int yrr = (int)ceil(y / yr);
    // printf("%lf %lf\n", y/yl, y/yr);
    // printf("%d %d\n", yll, yrr);
    if (xrr <= xll && yrr <= yll)
      ret++;
  }
  ans = max(ans, ret);
}

void work() {
  scanf("%d%d", &n, &p);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &b[i]);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 0; i < p; ++i) {
    c[i] = i;
  }
  ans = 0;
  calc();
  while (next_permutation(c, c + p)) {
    calc();
  }
  printf("%d\n", ans);
}

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0s.out", "w", stdout);
  int TC;
  scanf("%d", &TC);
  for (int tc = 1; tc <= TC; ++tc) {
    printf("Case #%d: ", tc);
    work();
  }
}
