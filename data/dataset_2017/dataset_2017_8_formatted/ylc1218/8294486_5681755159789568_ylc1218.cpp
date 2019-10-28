#include <cstdio>
#include <cstdlib>

int T, N, Q;
long long e[105], s[105], d[105][105];
double hourse[105][105];

int main() {
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; i++) {
      scanf("%d %d", &e[i], &s[i]);
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        scanf("%d", &d[i][j]);
      }
      d[i][i] = 0;
    }

    for (int k = 1; k <= N; k++) {
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          if (d[i][k] != -1 && d[k][j] != -1) {
            if (d[i][j] == -1 || d[i][k] + d[k][j] < d[i][j]) {
              d[i][j] = d[i][k] + d[k][j];
            }
          }
        }
      }
    }

    /*printf("---\n");
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }
    printf("---\n");*/

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        if (i == j) {
          hourse[i][j] = 0;
          continue;
        }
        if (d[i][j] != -1 && d[i][j] <= e[i]) {
          hourse[i][j] = d[i][j] / (double)s[i];
        } else {
          hourse[i][j] = -1;
        }
      }
    }

    /*printf("-hourse--\n");
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            printf("%lf ", hourse[i][j]);
        }
        printf("\n");
    }
    printf("---\n");*/

    for (int k = 1; k <= N; k++) {
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          if (hourse[i][k] != -1 && hourse[k][j] != -1) {
            if (hourse[i][j] == -1 ||
                hourse[i][k] + hourse[k][j] < hourse[i][j]) {
              hourse[i][j] = hourse[i][k] + hourse[k][j];
            }
          }
        }
      }
    }

    printf("Case #%d:", t);
    while (Q--) {
      int x, y;
      scanf("%d%d", &x, &y);
      printf(" %lf", hourse[x][y]);
    }
    printf("\n");
  }
  return 0;
}
