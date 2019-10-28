#include <cmath>
#include <cstring>
#include <stdio.h>

using namespace std;

int R, C;
char cake[50][50];

void solve() {
  for (int i = 0; i < R; i++) {
    for (int j = 1; j < C; j++) {
      if (cake[i][j] == '?') {
        cake[i][j] = cake[i][j - 1];
      }
    }
    for (int j = C - 2; j >= 0; j--) {
      if (cake[i][j] == '?') {
        cake[i][j] = cake[i][j + 1];
      }
    }
  }

  for (int j = 0; j < C; j++) {
    for (int i = 1; i < R; i++) {
      if (cake[i][j] == '?') {
        cake[i][j] = cake[i - 1][j];
      }
    }
    for (int i = R - 2; i >= 0; i--) {
      if (cake[i][j] == '?') {
        cake[i][j] = cake[i + 1][j];
      }
    }
  }

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      printf("%c", cake[i][j]);
    }
    puts("");
  }
}

int main() {
  int T;

  scanf(" %d", &T);
  for (int cas = 1; cas <= T; cas++) {
    scanf(" %d %d", &R, &C);
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        scanf(" %c", &cake[i][j]);
      }
    }

    printf("Case #%d:\n", cas);
    solve();
  }

  return 0;
}
