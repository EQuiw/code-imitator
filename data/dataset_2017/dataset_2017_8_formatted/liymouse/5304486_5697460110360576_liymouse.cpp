#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef long long i64d;

using namespace std;

int f[1005][1005] = {0}, c[1005][1005] = {0};
int L[1005] = {0}, p[1005] = {0};
int n, s, t, minv;

int ford() {
  int i, j, m, x;

  for (i = 1; i <= n; i++) {
    L[i] = 0;
    p[i] = 0;
  }
  L[s] = 1;
  while (1) {
    i = 1;
    while ((i <= n) && !((L[i] != 0) && (p[i] == 0)))
      i++;
    if (i > n)
      return 1;
    for (j = 1; j <= n; j++)
      if ((L[j] == 0) && ((c[i][j] > 0) || (c[j][i] > 0))) {
        if (f[i][j] < c[i][j])
          L[j] = i;
        if (f[j][i] > 0)
          L[j] = -i;
      }
    p[i] = 1;
    if (L[t] != 0)
      break;
  }
  m = t;
  minv = 32767;
  while (m != s) {
    j = m;
    m = (int)abs(L[j]);
    if (L[j] < 0)
      x = f[j][m];
    if (L[j] > 0)
      x = c[m][j] - f[m][j];
    if (x < minv)
      minv = x;
  }
  return 0;
}

void change() {
  int m, j;

  m = t;
  while (m != s) {
    j = m;
    m = (int)abs(L[j]);
    if (L[j] < 0)
      f[j][m] = f[j][m] - minv;
    if (L[j] > 0)
      f[m][j] = f[m][j] + minv;
  }
}

int maxvflow() {
  int del, success;

  // s = 1; t = n;
  success = 0;
  while (1) {
    success = ford();
    if (success == 1) {
      int maxv = 0;
      for (int i = 1; i <= n; i++) {
        if (f[i][t] != 0)
          maxv += f[i][t];
      }
      return maxv;
    } else
      change();
  }
}

int a[55][55], b[55][55];
int nn, pp;

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);
  int cas;
  scanf("%d", &cas);
  for (int ca = 1; ca <= cas; ca++) {
    printf("Case #%d: ", ca);

    scanf("%d %d", &nn, &pp);
    int se[55];

    for (int i = 0; i < nn; i++)
      scanf("%d", &se[i]);
    for (int i = 0; i < nn; i++) {
      for (int j = 0; j < pp; j++) {
        int x;
        scanf("%d", &x);
        a[i][j] = ceil(x / 1.1 / se[i]);
        b[i][j] = floor(x / 0.9 / se[i]);
      }
    }

    memset(f, 0, sizeof(f));
    memset(c, 0, sizeof(c));
    memset(L, 0, sizeof(L));
    memset(p, 0, sizeof(p));
    n = nn * pp + 2;
    s = n - 1;
    t = n;
    for (int i = 0; i < pp; i++)
      if (a[0][i] <= b[0][i]) {
        c[s][i + 1] = 1;
      }
    for (int i = 0; i < pp; i++)
      if (a[nn - 1][i] <= b[nn - 1][i]) {
        c[(nn - 1) * pp + i + 1][t] = 1;
      }
    for (int i = 1; i < nn; i++) {
      for (int k = 0; k < pp; k++)
        for (int y = 0; y < pp; y++) {
          int aa = max(a[i - 1][k], a[i][y]);
          int bb = min(b[i - 1][k], b[i][y]);
          if (aa <= bb)
            c[(i - 1) * pp + k + 1][i * pp + y + 1] = 1;
        }
    }
    int maxv = maxvflow();
    printf("%d\n", maxv);
  }
  return 0;
}