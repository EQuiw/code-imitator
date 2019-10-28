#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

#include <fstream>
FILE *fin = freopen("a.in", "r", stdin);
FILE *fout = freopen("a.out", "w", stdout);

int T, t, n, Q, i, j, k, h[110][2], x, y;
long long g[110][110];
double d[110], temp, m;
bool v[110];

int main() {
  double my, mx;
  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> n >> Q;
    for (i = 0; i < n; i++) {
      scanf("%d%d", &h[i][0], &h[i][1]);
    }
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        scanf("%d", &k);
        g[i][j] = k;
      }
    }
    for (k = 0; k < n; k++) {
      for (i = 0; i < n; i++)
        if (k != i) {
          for (j = 0; j < n; j++)
            if (i != j && k != j && g[i][k] >= 0 && g[k][j] >= 0) {
              if (g[i][j] == -1 || g[i][j] > g[i][k] + g[k][j]) {
                g[i][j] = g[i][k] + g[k][j];
              }
            }
        }
    }
    printf("Case #%d:", t);
    for (; Q; Q--) {
      scanf("%d%d", &x, &y);
      x--;
      y--;
      memset(v, 0, sizeof(v));
      for (i = 0; i < n; i++) {
        d[i] = -2;
      }
      d[x] = 0;
      while (1) {
        m = 99999999999999.0;
        k = -1;
        for (i = 0; i < n; i++) {
          if (!v[i] && d[i] > -1 && d[i] < m) {
            m = d[i];
            k = i;
          }
        }
        if (k == y)
          break;
        v[k] = 1;
        for (i = 0; i < n; i++) {
          if (!v[i] && g[k][i] > -1 && g[k][i] <= h[k][0]) {
            temp = d[k] + 1.0 * g[k][i] / h[k][1];
            if (d[i] < 0 || d[i] > temp) {
              d[i] = temp;
            }
          }
        }
      }
      printf(" %.9f", d[y]);
    }

    printf("\n");
  }
  return 0;
}
