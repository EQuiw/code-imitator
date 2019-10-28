// PLUS MANUAL FIXES
#include <stdio.h>
#include <string.h>

int D, N, K[1000], S[1000];
int i;

int main() {
  int cases;
  scanf("%d", &cases);
  for (int kejs = 1; kejs <= cases; kejs++) {
    printf("Case #%d: ", kejs);
    scanf("%d%d", &D, &N);
    double tmax = 0;
    for (i = 0; i < N; i++) {
      scanf("%d%d", &K[i], &S[i]);
      double s = D - K[i];
      double v = S[i];
      double t = s / v;
      if (t > tmax)
        tmax = t;
    }
    printf("%.10lf\n", D / tmax);
  }
  return 0;
}
