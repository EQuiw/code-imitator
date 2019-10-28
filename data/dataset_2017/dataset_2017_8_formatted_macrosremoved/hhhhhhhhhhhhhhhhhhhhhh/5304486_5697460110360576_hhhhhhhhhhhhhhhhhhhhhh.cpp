#include <bits/stdc++.h>
using namespace std;

int a[60], mat[60][60];

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);
  int test;
  scanf("%d", &test);
  for (int _ = 1; _ <= test; _++) {
    int n, P;
    scanf("%d%d", &n, &P);

    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < P; j++) {
        scanf("%d", &mat[i][j]);
      }
    }
    int ret = 0;
    if (2 == n) {
      sort(mat[1], mat[1] + P);
      do {
        int nowtot = 0;
        for (int i = 0; i < P; i++) {
          bool judge = false;
          for (int k = mat[0][i] / 1.1 / a[0]; k <= mat[0][i] / 0.9 / a[0] + 1;
               k++) {
            bool hav = ((mat[0][i] >= 0.9 * a[0] * k - 0.5) &&
                        (mat[0][i] <= 1.1 * a[0] * k + 0.5) &&
                        (mat[1][i] >= 0.9 * a[1] * k - 0.5) &&
                        (mat[1][i] <= 1.1 * a[1] * k + 0.5));
            if (hav) {
              judge = true;
              break;
            }
          }
          if (judge)
            nowtot++;
        }
        ret = max(ret, nowtot);
      } while (next_permutation(mat[1], mat[1] + P));
    } else {
      for (int i = 0; i < P; i++) {
        bool judge = false;
        for (int k = mat[0][i] / 1.1 / a[0]; k <= mat[0][i] / 0.9 / a[0] + 1;
             k++) {
          bool hav = ((mat[0][i] >= 0.9 * a[0] * k - 0.5) &&
                      (mat[0][i] <= 1.1 * a[0] * k + 0.5));
          if (hav) {
            judge = true;
            break;
          }
        }
        if (judge)
          ret++;
      }
    }

    printf("Case #%d: %d\n", _, ret);
  }
  return 0;
}
