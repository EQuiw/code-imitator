#include <stdio.h>

double n;
int m;
double mx;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, i;
  scanf("%d", &t);

  for (int tt = 1; tt <= t; tt++) {
    scanf("%lf%d", &n, &m);
    mx = 0;
    for (i = 1; i <= m; i++) {
      double a, b;
      scanf("%lf%lf", &a, &b);
      if ((n - a) / b > mx) {
        mx = (n - a) / b;
      }
    }

    printf("Case #%d: %.6lf\n", tt, n / mx);
  }
  return 0;
}