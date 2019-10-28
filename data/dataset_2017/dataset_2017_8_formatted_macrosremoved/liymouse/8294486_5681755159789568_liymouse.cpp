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

double s[110][110];
int d[110][110];
int n;
void dij(int x, int he, int hs) {
  int mark[110] = {0};
  int dis[110] = {0};
  for (int i = 0; i < n; i++)
    if (d[x][i] == -1 || d[x][i] > he)
      s[x][i] = -1;
    else {
      s[x][i] = (double)d[x][i] / hs;
      dis[i] = d[x][i];
    }
  mark[x] = 1;
  for (int i = 0; i < n; i++) {
    int k = -1;
    double mint = 1e20;
    for (int j = 0; j < n; j++)
      if (mark[j] == 0 && (s[x][j] > 0 && s[x][j] < mint)) {
        k = j;
        mint = s[x][j];
      }
    if (k == -1)
      break;
    mark[k] = 1;
    for (int j = 0; j < n; j++)
      if (mark[j] == 0 && (d[k][j] != -1 && dis[k] + d[k][j] <= he) &&
          (s[x][j] < 0 || s[x][k] + (double)d[k][j] / hs < s[x][j])) {
        s[x][j] = s[x][k] + (double)d[k][j] / hs;
        dis[j] = dis[k] + d[k][j];
      }
  }
}

int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-small-attempt0.out", "w", stdout);
  // freopen("B-large.in" , "r" , stdin);
  // freopen("B-large.out" , "w" , stdout);
  int cas;
  scanf("%d", &cas);
  for (int ca = 1; ca <= cas; ca++) {
    printf("Case #%d:", ca);
    int q;
    int he[110], hs[110];

    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++)
      scanf("%d %d", &he[i], &hs[i]);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        scanf("%d", &d[i][j]);
        s[i][j] = -1;
      }

    for (int i = 0; i < n; i++) {
      dij(i, he[i], hs[i]);
    }

    for (int k = 0; k < n; k++)
      for (int i = 0; i < n; i++)
        if (i != k)
          for (int j = 0; j < n; j++)
            if (j != i && j != k && s[i][k] > 0 && s[k][j] > 0 &&
                (s[i][j] < 0 || s[i][k] + s[k][j] < s[i][j])) {
              s[i][j] = s[i][k] + s[k][j];
            }
    for (int i = 0; i < q; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      printf(" %lf", s[x - 1][y - 1]);
    }
    printf("\n");
  }
  return 0;
}
