#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

void work() {
  double D;
  int n;
  scanf("%lf%d", &D, &n);
  double ans = 1e20;
  for (int i = 0; i < n; ++i) {
    double x, y;
    scanf("%lf%lf", &x, &y);
    ans = min(ans, D / ((D - x) / y));
  }
  printf("%lf\n", ans);
}

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int TC;
  scanf("%d", &TC);
  for (int tc = 1; tc <= TC; ++tc) {
    printf("Case #%d: ", tc);
    work();
  }
}