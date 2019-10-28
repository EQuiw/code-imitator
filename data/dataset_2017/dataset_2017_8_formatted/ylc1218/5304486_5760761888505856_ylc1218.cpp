#include <cstdio>
#include <cstdlib>

int T, R, C;
char grid[30][30];

int main() {
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d%d", &R, &C);
    for (int r = 0; r < R; r++) {
      scanf("%s", grid[r]);
    }

    for (int r = 0; r < R; r++) {
      for (int c = 0; c < C; c++) {
        // fill row
        if (grid[r][c] != '?') {
          int cc = c - 1;
          while (cc >= 0 && grid[r][cc] == '?') {
            grid[r][cc] = grid[r][c];
            cc--;
          }
          cc = c + 1;
          while (cc < C && grid[r][cc] == '?') {
            grid[r][cc] = grid[r][c];
            cc++;
          }
        }
      }
    }

    // for each empty row
    for (int r = 0; r < R; r++) {
      if (grid[r][0] != '?') {
        int rr = r - 1;
        while (rr >= 0 && grid[rr][0] == '?') {
          for (int c = 0; c < C; c++) {
            grid[rr][c] = grid[r][c];
          }
          rr--;
        }

        rr = r + 1;
        while (rr < R && grid[rr][0] == '?') {
          for (int c = 0; c < C; c++) {
            grid[rr][c] = grid[r][c];
          }
          rr++;
        }
      }
    }
    printf("Case #%d:\n", t);
    for (int r = 0; r < R; r++) {
      printf("%s\n", grid[r]);
    }
  }
  return 0;
}
