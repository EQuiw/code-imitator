#include <bits/stdc++.h>
using namespace std;

#define maxn 50
char a[maxn][maxn];

int main() {
  int test, n, m, kase = 0;
  scanf("%d", &test);
  while (test--) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
      scanf("%s", a[i]);
    }

    for (int foo = 0; foo < 100; foo++) {
      for (int i = 0; i < n; i++) {
        int ok = 0;
        for (int j = 0; j < m; j++) {
          if (a[i][j] != '?') {
            ok = 1;
            for (int k = j - 1; k >= 0 && a[i][k] == '?'; k--) {
              a[i][k] = a[i][j];
            }

            for (int k = j + 1; k < m && a[i][k] == '?'; k++) {
              a[i][k] = a[i][j];
            }
          }
        }

        int check = 0;
        if (i != 0) {
          for (int j = 0; j < m; j++) {
            if (a[i - 1][j] != '?')
              check = 1;
          }

          if (check == 0) {
            for (int j = 0; j < m; j++)
              a[i - 1][j] = a[i][j];
          }
        }

        check = 0;
        if (i != n - 1) {
          for (int j = 0; j < m; j++) {
            if (a[i + 1][j] != '?') {
              check = 1;
            }
          }

          if (check == 0) {
            for (int j = 0; j < m; j++)
              a[i + 1][j] = a[i][j];
          }
        }
      }
    }

    printf("Case #%d:\n", ++kase);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        printf("%c", a[i][j]);
      }
      puts("");
    }
  }
  return 0;
}