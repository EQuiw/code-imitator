#include <algorithm>
#include <cstdio>
#include <queue>

using std::max;
using std::min;
using std::queue;

int rmin[26], rmax[26], cmin[26], cmax[26];
bool appear[26];
int T, R, C;
char in[30][30];

bool empty(int rl, int rr, int cl, int cr) {
  for (int r = rl; r <= rr; r++) {
    for (int c = cl; c <= cr; c++) {
      if (in[r][c] != '?') {
        return false;
      }
    }
  }
  return true;
}

void fill(int rl, int rr, int cl, int cr, char ch) {
  for (int r = rl; r <= rr; r++) {
    for (int c = cl; c <= cr; c++) {
      in[r][c] = ch;
    }
  }
}

int main() {
  freopen("A-small-attempt1.in", "r", stdin);
  freopen("A-small-attempt1.out", "w", stdout);
  scanf("%d", &T);
  for (int tc = 1; tc <= T; tc++) {
    scanf("%d%d", &R, &C);
    for (int i = 0; i < 26; i++) {
      rmin[i] = R;
      rmax[i] = 1;
      cmin[i] = C;
      cmax[i] = 1;
    }
    for (int i = 1; i <= R; i++) {
      scanf("%s", in[i] + 1);
      for (int j = 1; j <= C; j++) {
        if (in[i][j] != '?') {
          int ord = in[i][j] - 'A';
          appear[ord] = true;
          rmin[ord] = min(rmin[ord], i);
          rmax[ord] = max(rmax[ord], i);
          cmin[ord] = min(cmin[ord], j);
          cmax[ord] = max(cmax[ord], j);
        }
      }
    }
    while (true) {
      bool adj = false;
      // r stretch
      for (int ord = 0; ord < 26; ord++) {
        if (appear[ord]) {
          while (rmin[ord] - 1 >= 1 &&
                 empty(rmin[ord] - 1, rmin[ord] - 1, cmin[ord], cmax[ord])) {
            adj = true;
            rmin[ord]--;
            fill(rmin[ord], rmin[ord], cmin[ord], cmax[ord], ord + 'A');
          }
          while (rmax[ord] + 1 <= R &&
                 empty(rmax[ord] + 1, rmax[ord] + 1, cmin[ord], cmax[ord])) {
            adj = true;
            rmax[ord]++;
            fill(rmax[ord], rmax[ord], cmin[ord], cmax[ord], ord + 'A');
          }
        }
      }
      // c stretch
      for (int ord = 0; ord < 26; ord++) {
        if (appear[ord]) {
          while (cmin[ord] - 1 >= 1 &&
                 empty(rmin[ord], rmax[ord], cmin[ord] - 1, cmin[ord] - 1)) {
            adj = true;
            cmin[ord]--;
            fill(rmin[ord], rmax[ord], cmin[ord], cmin[ord], ord + 'A');
          }
          while (cmax[ord] + 1 <= C &&
                 empty(rmin[ord], rmax[ord], cmax[ord] + 1, cmax[ord] + 1)) {
            adj = true;
            cmax[ord]++;
            fill(rmin[ord], rmax[ord], cmax[ord], cmax[ord], ord + 'A');
          }
        }
      }
      if (!adj)
        break;
    }
    printf("Case #%d:\n", tc);
    for (int i = 1; i <= R; i++) {
      printf("%s\n", in[i] + 1);
    }
  }
  return 0;
}
