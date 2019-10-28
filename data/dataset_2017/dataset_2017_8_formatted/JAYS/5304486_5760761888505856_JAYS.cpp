#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int R, C;
char G[33][33];

char ans[33][33];
int n[33];

void solve() {
  memset(n, 0, sizeof(n));
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      if (G[r][c] != '?')
        n[G[r][c] - 'A']++;
    }
  }
  for (int i = 0; i < 26; i++) {
    if (n[i] >= 2) {
      char ch = i + 'A';
      int minr = 33, minc = 33, maxr = 0, maxc = 0;
      for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
          if (G[r][c] == ch) {
            minr = min(minr, r), minc = min(minc, c);
            maxr = max(maxr, r), maxc = max(maxc, c);
          }
        }
      }
      for (int r = minr; r <= maxr; r++) {
        for (int c = minc; c <= maxc; c++) {
          if (G[r][c] == '?')
            G[r][c] = ch;
          assert(G[r][c] == ch);
        }
      }
    }
  }
  for (int i = 0; i < 26; i++) {
    if (n[i] == 1) {
      char ch = i + 'A';
      int rr, cc;
      for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
          if (G[r][c] == ch)
            rr = r, cc = c;
      int c = cc;
      for (int c = cc - 1; c >= 0; c--) {
        if (G[rr][c] != '?')
          break;
        G[rr][c] = ch;
      }
      for (int c = cc + 1; c < C; c++) {
        if (G[rr][c] != '?')
          break;
        G[rr][c] = ch;
      }
    }
  }
  while (1) {
    for (int r = 0; r < R; r++) {
      bool filled = true;
      for (int c = 0; c < C; c++)
        if (G[r][c] == '?')
          filled = false;
      if (filled) {
        if (r - 1 >= 0) {
          bool all = true;
          for (int c = 0; c < C; c++)
            if (G[r - 1][c] != '?')
              all = false;
          if (all)
            for (int c = 0; c < C; c++)
              G[r - 1][c] = G[r][c];
        }
        if (r + 1 < R) {
          bool all = true;
          for (int c = 0; c < C; c++)
            if (G[r + 1][c] != '?')
              all = false;
          if (all)
            for (int c = 0; c < C; c++)
              G[r + 1][c] = G[r][c];
        }
      }
    }
    bool finished = true;
    for (int r = 0; r < R; r++)
      for (int c = 0; c < C; c++)
        if (G[r][c] == '?')
          finished = false;
    if (finished)
      break;
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d%d", &R, &C);
    for (int r = 0; r < R; r++)
      scanf("%s", G[r]);
    printf("Case #%d:\n", t);
    solve();
    for (int r = 0; r < R; r++) {
      for (int c = 0; c < C; c++) {
        printf("%c", G[r][c]);
      }
      printf("\n");
    }
  }
  return 0;
}