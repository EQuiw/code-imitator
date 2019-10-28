#include <bits/stdc++.h>

using namespace std;

//#define LARGE

char cake[30][30];

int main() {

  freopen("A-small.in", "r", stdin);
  freopen("A-small.out", "w", stdout);

  int T;
  scanf("%d", &T);
  for (int Case = 1; Case <= T; ++Case) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
      scanf("%s", cake[i]);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (cake[i][j] != '?') {
          int j0 = j + 1;
          while (j0 < m && cake[i][j0] == '?') {
            cake[i][j0++] = cake[i][j];
          }
          j0 = j - 1;
          while (j0 > -1 && cake[i][j0] == '?') {
            cake[i][j0--] = cake[i][j];
          }
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (cake[i][j] != '?') {
          int i0 = i + 1;
          while (i0 < n && cake[i0][j] == '?') {
            cake[i0++][j] = cake[i][j];
          }
          i0 = i - 1;
          while (i0 < n && cake[i0][j] == '?') {
            cake[i0--][j] = cake[i][j];
          }
        }
      }
    }
    printf("Case #%d:\n", Case);
    for (int i = 0; i < n; ++i)
      printf("%s\n", cake[i]);
  }
  return 0;
}
