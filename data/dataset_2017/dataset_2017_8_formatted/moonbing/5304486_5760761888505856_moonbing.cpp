#include <stdio.h>

int T;
int R, C;
char map[30][30];

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  int i, j, k;

  scanf("%d", &T);
  for (t = 1; t <= T; t++) {
    scanf("%d %d", &R, &C);
    for (i = 0; i < R; i++)
      scanf("%s", map[i]);

    for (i = 0; i < R; i++) {
      for (j = 0; j < C; j++) {
        if (map[i][j] == '?') {
          if (j - 1 >= 0 && map[i][j - 1] != '?')
            map[i][j] = map[i][j - 1];
        }
      }
      for (j = C - 1; j >= 0; j--) {
        if (map[i][j] == '?') {
          if (j + 1 < C && map[i][j + 1] != '?')
            map[i][j] = map[i][j + 1];
        }
      }
    }
    for (i = 0; i < R; i++) {
      for (j = 0; j < C; j++) {
        if (map[i][j] == '?' && i - 1 >= 0) {
          map[i][j] = map[i - 1][j];
        }
      }
    }
    for (i = R - 1; i >= 0; i--) {
      for (j = 0; j < C; j++) {
        if (map[i][j] == '?' && i + 1 < R) {
          map[i][j] = map[i + 1][j];
        }
      }
    }

    printf("Case #%d:\n", t);
    for (i = 0; i < R; i++)
      printf("%s\n", map[i]);
  }

  return 0;
}