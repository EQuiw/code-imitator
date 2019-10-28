// PLUS MANUAL FIXES
#include <stdio.h>
#include <string.h>

char a[25][26];
bool was[255];
int R, C, i, j, k, b, e, q;

int main() {
  int cases;
  scanf("%d", &cases);
  for (int kejs = 1; kejs <= cases; kejs++) {
    printf("Case #%d:\n", kejs);
    scanf("%d%d", &R, &C);
    for (i = 0; i < R; i++)
      scanf("%s", a[i]);
    for (i = 'A'; i <= 'Z'; i++)
      was[i] = false;
    if (kejs == 67)
      for (i = 0; i < R; i++)
        printf("%s\n", a[i]);

    for (i = 0; i < R; i++) {
      for (j = 0; j < C; j++) {
        if (a[i][j] != '?' && !was[(int)a[i][j]]) {
          was[(int)a[i][j]] = true;

          for (k = i - 1; k >= 0; k--)
            if (a[k][j] == '?')
              a[k][j] = a[i][j];
            else
              break;
          b = k + 1;
          for (k = i + 1; k < R; k++)
            if (a[k][j] == '?')
              a[k][j] = a[i][j];
            else
              break;
          e = k - 1;
          for (k = j - 1; k >= 0; k--) {
            for (q = b; q <= e; q++)
              if (a[q][k] != '?')
                break;
            if (q > e) {
              for (q = b; q <= e; q++)
                a[q][k] = a[i][j];
            } else
              break;
          }
          for (k = j + 1; k < C; k++) {
            for (q = b; q <= e; q++)
              if (a[q][k] != '?')
                break;
            if (q > e) {
              for (q = b; q <= e; q++)
                a[q][k] = a[i][j];
            } else
              break;
          }
        }
      }
    }

    for (i = 0; i < R; i++)
      printf("%s\n", a[i]);
  }
  return 0;
}
