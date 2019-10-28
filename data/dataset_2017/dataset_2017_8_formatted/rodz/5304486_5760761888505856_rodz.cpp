#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

char grid[27][27];
int vis[27][27];

int countt(int i1, int j1, int i2, int j2) {
  int mask = 0;
  for (int i = i1; i <= i2; i++) {
    for (int j = j1; j <= j2; j++) {
      if (grid[i][j] != '?')
        mask |= (1 << (grid[i][j] - 'A'));
    }
  }
  return mask;
}

void paint(int i1, int j1, int i2, int j2, char c) {
  for (int i = i1; i <= i2; i++) {
    for (int j = j1; j <= j2; j++) {
      vis[i][j] = 1;
      grid[i][j] = c;
    }
  }
}

int main() {
  int t, casecnt = 1;
  scanf("%d", &t);
  while (t--) {
    int r, c;
    scanf("%d %d", &r, &c);
    for (int i = 0; i < r; i++)
      scanf("%s", grid[i]);
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (vis[i][j])
          continue;
        int ei = i, ej = j;
        char l;
        for (int ii = i; ii < r; ii++) {
          for (int jj = j; jj < c; jj++) {
            int mask = countt(i, j, ii, jj);
            if (__builtin_popcount(mask) == 1) {
              if ((ii - i + 1) * (jj - j + 1) >= (ei - i + 1) * (ej - j + 1)) {
                ei = ii;
                ej = jj;
                l = 'A' + __builtin_ctz(mask);
              }
            }
          }
        }
        paint(i, j, ei, ej, l);
      }
    }
    printf("Case #%d:\n", casecnt++);
    for (int i = 0; i < r; i++)
      printf("%s\n", grid[i]);
  }
  return 0;
}
