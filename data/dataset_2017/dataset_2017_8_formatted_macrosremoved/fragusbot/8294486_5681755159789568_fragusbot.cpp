#include <bits/stdc++.h>

using namespace std;

const long long inf = 4e18;
const int N = 123;

int a[N];
int b[N];
long long d[N][N];
long double f[N];
bool was[N];

int main() {
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
  int tt;
  scanf("%d", &tt);
  for (int cc = 1; cc <= tt; ++cc) {
    double begt = clock();
    printf("Case #%d: ", cc);
    int n, qq;
    scanf("%d %d", &n, &qq);
    for (int i = 0; i < n; ++i) {
      scanf("%d %d", a + i, b + i);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int foo;
        scanf("%d", &foo);
        d[i][j] = (foo == -1 ? inf : foo);
      }
    }
    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
      }
    }
    for (int q = 0; q < qq; ++q) {
      if (q > 0)
        putchar(' ');
      int from, to;
      scanf("%d %d", &from, &to);
      --from;
      --to;
      for (int i = 0; i < n; ++i) {
        f[i] = inf;
      }
      memset(was, false, sizeof was);
      was[from] = true;
      f[from] = 0;
      int x = from;
      for (int it = 0; it < n - 1; ++it) {
        for (int y = 0; y < n; ++y) {
          if (d[x][y] > a[x]) {
            continue;
          }
          long double cur = f[x] + (long double)d[x][y] / b[x];
          if (cur < f[y]) {
            f[y] = cur;
          }
        }
        x = -1;
        for (int y = 0; y < n; ++y) {
          if (was[y]) {
            continue;
          }
          if (x == -1 || f[y] < f[x]) {
            x = y;
          }
        }
        was[x] = true;
      }
      printf("%.15f", (double)f[to]);
    }
    putchar('\n');
    fprintf(stderr, "case %d solved in %.3f\n", cc,
            (clock() - begt) / CLOCKS_PER_SEC);
  }
}
