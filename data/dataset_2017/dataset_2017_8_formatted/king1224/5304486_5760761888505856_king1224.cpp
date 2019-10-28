#include <cstdio>
#include <cstring>

int main() {
  int T, R, C;
  char a[30][30];
  bool col[30];
  scanf("%d", &T);
  for (int rr = 1; rr <= T; ++rr) {
    scanf("%d %d", &R, &C);
    memset(a, 0, sizeof(a));
    memset(col, false, sizeof(col));
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        scanf("%c", &a[i][j]);
        while ((a[i][j] < 'A' || a[i][j] > 'Z') && a[i][j] != '?')
          scanf("%c", &a[i][j]);
        if (a[i][j] != '?')
          col[j] = true;
      }
    }

    for (int i = 1; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        if (a[i][j] == '?' && a[i - 1][j] != '?') {
          a[i][j] = a[i - 1][j];
        }
      }
    }
    for (int i = R - 1; i > 0; --i) {
      for (int j = 0; j < C; ++j) {
        if (a[i][j] != '?' && a[i - 1][j] == '?') {
          a[i - 1][j] = a[i][j];
        }
      }
    }

    for (int i = 1; i < C; ++i) {
      if (!col[i] && col[i - 1]) {
        for (int j = 0; j < R; ++j)
          a[j][i] = a[j][i - 1];
        col[i] = true;
      }
    }
    for (int i = C - 2; i >= 0; --i) {
      if (!col[i] && col[i + 1]) {
        for (int j = 0; j < R; ++j)
          a[j][i] = a[j][i + 1];
        col[i] = true;
      }
    }

    printf("Case #%d:\n", rr);
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        printf("%c", a[i][j]);
      }
      puts("");
    }
  }
  return 0;
}
