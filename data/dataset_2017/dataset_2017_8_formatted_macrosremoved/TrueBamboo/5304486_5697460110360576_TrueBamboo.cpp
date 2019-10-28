#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

#include <fstream>
FILE *fin = freopen("a.in", "r", stdin);
FILE *fout = freopen("a.out", "w", stdout);

inline int calmax(int a, int b) { return floor(1.0 * b / 0.9 / a); }

inline int calmin(int a, int b) { return ceil(1.0 * b / 1.1 / a); }
int s[1200100][60];

int main() {
  int T, t, n, p, i, j, k, a[60], g[60][60], b[60][60][2], tot, l[60];
  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> n >> p;
    for (i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    for (i = 0; i < n; i++) {
      for (j = 0; j < p; j++) {
        scanf("%d", &g[i][j]);
      }
      sort(g[i], g[i] + p);
    }
    for (i = 0; i < n; i++) {
      for (j = 0; j < p; j++) {
        b[i][j][0] = calmin(a[i], g[i][j]);
        b[i][j][1] = calmax(a[i], g[i][j]);
      }
    }
    memset(s, 0, sizeof(s));
    tot = 0;
    for (i = 0; i < n; i++) {
      l[i] = p - 1;
      for (j = 0; j < p; j++) {
        for (k = b[i][j][0]; k <= b[i][j][1]; k++) {
          s[k][i]++;
        }
      }
    }
    for (i = 1200000; i;) {
      for (j = 0; j < n; j++) {
        if (s[i][j] == 0) {
          break;
        }
      }
      if (j == n) {
        tot++;
        for (j = 0; j < n; j++) {
          while (l[j] >= 0 && b[j][l[j]][0] > i) {
            l[j]--;
          }
          for (k = b[j][l[j]][0]; k <= b[j][l[j]][1]; k++) {
            s[k][j]--;
          }
          l[j]--;
        }
      } else {
        i--;
      }
    }
    printf("Case #%d: %d\n", t, tot);
  }
  return 0;
}
