#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

const int MN = 1010;

int T;
int N, R, O, Y, G, B, V;
bool dp[MN][MN / 2][MN / 2][3];
char tr[MN][MN / 2][MN / 2][3];

inline void update(int pre, int i, int ri, int yi, int p) {
  if (!dp[i][ri][yi][p]) {
    dp[i][ri][yi][p] = true;
    tr[i][ri][yi][p] = pre;
  }
}

void trace(int i, int ri, int yi, int p) {
  if (i == 0)
    return;
  int pre = tr[i][ri][yi][p];
  if (!dp[i][ri][yi][p])
    printf("WTFFFFFFFFFFFF\n");
  if (p == 0) {
    trace(i - 1, ri - 1, yi, pre);
    printf("R");
  }
  if (p == 1) {
    trace(i - 1, ri, yi - 1, pre);
    printf("Y");
  }
  if (p == 2) {
    trace(i - 1, ri, yi, pre);
    printf("B");
  }
}

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);

  scanf("%d", &T);
  for (int tc = 1; tc <= T; tc++) {
    scanf("%d%d%d%d%d%d%d", &N, &R, &O, &Y, &G, &B, &V);
    for (int i = 1; i <= N; i++) {
      for (int ri = 0; ri <= R; ri++) {
        for (int yi = 0; yi <= Y; yi++) {
          for (int p = 0; p < 3; p++) {
            dp[i][ri][yi][p] = false;
            tr[i][ri][yi][p] = 0;
          }
        }
      }
    }
    if (B == 0) {
      if (R == 0 && Y == 1) {
        printf("Case #%d: Y\n", tc);
      } else if (R == 1 && Y == 0) {
        printf("Case #%d: R\n", tc);
      } else if (R == Y) {
        printf("Case #%d: ", tc);
        for (int ri = 0; ri < R; ri++) {
          printf("RY");
        }
        printf("\n");
      } else {
        printf("Case #%d: IMPOSSIBLE\n", tc);
      }
    } else if (R == 0 && Y == 0 && B == 1) {
      printf("Case #%d: B\n", tc);
    } else if (R + R > N || Y + Y > N || B + B > N) {
      printf("Case #%d: IMPOSSIBLE\n", tc);
    } else {
      // 0R 1Y 2B
      dp[1][0][0][2] = true;
      tr[1][0][0][2] = 0;
      for (int i = 1; i < N; i++) {
        for (int ri = 0; ri <= R; ri++) {
          if (ri + ri > i)
            break;
          for (int yi = 0; yi <= Y; yi++) {
            if (yi + yi > i)
              break;
            int bi = i - ri - yi;
            if (bi < 0)
              break;
            if (bi > B)
              continue;
            // printf("(%d,%d,%d): %d %d %d\n", ri, yi, bi, dp[i][ri][yi][0],
            // dp[i][ri][yi][1], dp[i][ri][yi][2]);
            if (dp[i][ri][yi][0]) {
              update(0, i + 1, ri, yi + 1, 1); // R->Y
              update(0, i + 1, ri, yi, 2);     // R->B
            }
            if (dp[i][ri][yi][1]) {
              update(1, i + 1, ri + 1, yi, 0); // Y->R
              update(1, i + 1, ri, yi, 2);     // Y->B
            }
            if (dp[i][ri][yi][2]) {
              update(2, i + 1, ri + 1, yi, 0); // B->R
              update(2, i + 1, ri, yi + 1, 1); // B->Y
            }
          }
        }
      }
      if (dp[N][R][Y][0]) {
        printf("Case #%d: ", tc);
        trace(N, R, Y, 0);
        printf("\n");
      } else if (dp[N][R][Y][1]) {
        printf("Case #%d: ", tc);
        trace(N, R, Y, 1);
        printf("\n");
      } else {
        printf("Case #%d: IMPOSSIBLE\n", tc);
      }
    }
  }
  return 0;
}
