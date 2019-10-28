

#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

char a[27][27];

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small.out", "w", stdout);

  int T;
  scanf("%d", &T);
  for (int cn = 1; cn <= T; ++cn) {
    memset(a, 0, sizeof(a));

    int R, C;
    scanf("%d%d", &R, &C);
    for (int i = 0; i < R; ++i)
      for (int j = 0; j < C; ++j)
        scanf(" %c", &a[i][j]);

    for (int j = 0; j < C; ++j) {
      for (int i = 0; i < R; ++i) {
        if (a[i][j] != '?') {
          for (int up = i - 1; up >= 0; --up) {
            if (a[up][j] == '?')
              a[up][j] = a[i][j];
            else
              break;
          }
          for (int down = i + 1; down < R; ++down) {
            if (a[down][j] == '?')
              a[down][j] = a[i][j];
            else
              break;
          }
        }
      }
    }

    for (int i = 0; i < C; ++i) {
      if (a[0][i] != '?') {
        for (int y = i - 1; y >= 0; --y) {
          if (a[0][y] == '?') {
            for (int x = 0; x < R; ++x)
              a[x][y] = a[x][i];
          } else
            break;
        }
        for (int y = i + 1; y < C; ++y) {
          if (a[0][y] == '?') {
            for (int x = 0; x < R; ++x)
              a[x][y] = a[x][i];
          } else
            break;
        }
      }
    }

    printf("Case #%d:\n", cn);
    for (int i = 0; i < R; ++i)
      printf("%s\n", a[i]);
  }
}
