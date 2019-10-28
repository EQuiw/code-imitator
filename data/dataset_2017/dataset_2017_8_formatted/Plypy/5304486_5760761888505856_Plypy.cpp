#include <bits/stdc++.h>
using namespace std;

int R, C;

char mat[30][30];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    printf("Case #%d: \n", cas);
    scanf("%d%d", &R, &C);
    for (int i = 0; i < R; ++i) {
      scanf("%s", mat[i]);
      mat[i][C] = 0;
    }
    for (int i = 0; i < R; ++i) {
      char fst = 0;
      for (int j = 0; j < C; ++j) {
        if (mat[i][j] != '?') {
          fst = mat[i][j];
          break;
        }
      }
      if (0 == fst) {
        continue;
      }
      for (int j = 0; j < C; ++j) {
        if (mat[i][j] == '?')
          mat[i][j] = fst;
        else
          fst = mat[i][j];
      }
    }
    for (int i = 0; i < R; ++i) {
      if (mat[i][0] != '?') {
        continue;
      }
      if (i > 0 && mat[i - 1][0] != '?') {
        memcpy(mat[i], mat[i - 1], C);
      }
    }
    for (int i = R - 1; i >= 0; --i) {
      if (mat[i][0] != '?') {
        continue;
      }
      if (i < R - 1 && mat[i + 1][0] != '?') {
        memcpy(mat[i], mat[i + 1], C);
      }
    }

    for (int i = 0; i < R; ++i)
      puts(mat[i]);
  }
}
