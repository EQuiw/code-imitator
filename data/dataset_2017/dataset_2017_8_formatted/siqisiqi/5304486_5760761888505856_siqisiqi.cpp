#include <cstdio>

char mat[30][30];

int cnt(int x0, int y0, int x1, int y1) {

  int cnt = 0;
  for (int i = x0; i < x1; ++i)
    for (int j = y0; j < y1; ++j)
      if (mat[i][j] != '?')
        cnt++;

  return cnt;
}
int get(int x0, int y0, int x1, int y1) {

  for (int i = x0; i < x1; ++i)
    for (int j = y0; j < y1; ++j)
      if (mat[i][j] != '?')
        return mat[i][j];
  return 0;
}

void cut(int x0, int y0, int x1, int y1) {

  int c = cnt(x0, y0, x1, y1);
  if (c == 1) {
    char x = get(x0, y0, x1, y1);
    for (int i = x0; i < x1; ++i)
      for (int j = y0; j < y1; ++j)
        mat[i][j] = x;
    return;
  }

  else {

    for (int k = x0 + 1; k < x1; ++k) {
      if (cnt(x0, y0, k, y1) && cnt(k, y0, x1, y1)) {
        cut(x0, y0, k, y1);
        cut(k, y0, x1, y1);
        return;
      }
    }
    for (int k = y0 + 1; k < y1; ++k) {
      if (cnt(x0, y0, x1, k) && cnt(x0, k, x1, y1)) {
        cut(x0, y0, x1, k);
        cut(x0, k, x1, y1);
        return;
      }
    }
  }
}
int main() {
  int T;
  scanf("%d", &T);
  for (int test = 1; test <= T; ++test) {

    int r, c;
    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        scanf(" %c ", &mat[i][j]);
      }
    }
    cut(0, 0, r, c);

    printf("Case #%d:\n", test);
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j)
        printf("%c", mat[i][j]);
      printf("\n");
    }
  }
  return 0;
}
