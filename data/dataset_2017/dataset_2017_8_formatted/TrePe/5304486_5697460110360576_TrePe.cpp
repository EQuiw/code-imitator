#include <math.h>
#include <stdio.h>

int N, P, R[50], Q[50][50], i, j, k, X, cnt;
bool was[50][50];

int main() {
  int cases;
  scanf("%d", &cases);
  for (int kejs = 1; kejs <= cases; kejs++) {
    printf("Case #%d: ", kejs);
    scanf("%d%d", &N, &P);
    for (i = 0; i < N; i++)
      scanf("%d", &R[i]);
    for (i = 0; i < N; i++) {
      for (j = 0; j < P; j++) {
        scanf("%d", &Q[i][j]);
        was[i][j] = false;
      }
    }
    // for (X = (int) ceil(10 * Q[0][i] / 11. / R[0]); 9 * X * R[0] <= 10 *
    // Q[0][i]; X++) {

    for (cnt = 0;; cnt++) {
      int maxX = -1;
      for (i = 0; i < N; i++) {
        int minX = -1;
        for (j = 0; j < P; j++) {
          if (was[i][j])
            continue;
          X = (int)ceil(10 * Q[i][j] / 11. / R[i]);
          if (9LL * X * R[i] <= 10 * Q[i][j]) {
            if (minX == -1 || minX > X) {
              minX = X;
            }
          }
        }
        if (maxX == -1 || maxX < minX)
          maxX = minX;
      }
      if (maxX == -1)
        break;
      for (i = 0; i < N; i++) {
        int minj = -1;
        for (j = 0; j < P; j++) {
          if (was[i][j])
            continue;
          if (9LL * maxX * R[i] <= 10 * Q[i][j]) {
            if (minj == -1 || Q[i][j] < Q[i][minj]) {
              minj = j;
            }
          }
        }
        if (minj == -1)
          break;
        was[i][minj] = true;
      }
      if (i < N)
        break;
    }
    printf("%d\n", cnt);
  }
  return 0;
}
