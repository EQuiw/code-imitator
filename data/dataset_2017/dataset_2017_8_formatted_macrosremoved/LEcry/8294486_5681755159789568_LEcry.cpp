//============================================================================
// Name        : A.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>

using namespace std;
double f[111][111];
long long dis[111][111];
int e[111], s[111];
int mp[111][111];
double dp[111][111];
bool bo[111][111];
struct node {
  int x, y;
  node() {}
  node(int xx, int yy) { x = xx, y = yy; }
} st[2111111];
int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-small-attempt0.out", "w", stdout);
  int tt, ri = 0;
  scanf("%d", &tt);
  while (tt--) {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
      scanf("%d%d", &e[i], &s[i]);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j) {
        scanf("%d", &mp[i][j]);
        dis[i][j] = mp[i][j];
      }
    for (int k = 1; k <= n; ++k) {
      for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
          if (dis[i][k] < 0 || dis[k][j] < 0)
            continue;
          if (dis[i][j] < 0 || dis[i][k] + dis[k][j] < dis[i][j])
            dis[i][j] = dis[i][k] + dis[k][j];
        }
      }
    }

    //		for(int i=1;i<=n;++i){
    //			for(int j=1;j<=n;++j){
    //				printf("%I64d ",dis[i][j]);
    //			}
    //			puts("");
    //		}
    printf("Case #%d:", ++ri);
    for (int cas = 0; cas < q; ++cas) {
      int u, k;
      scanf("%d %d", &u, &k);
      double f[111];
      f[1] = 0;
      for (int i = 2; i <= n; ++i) {
        f[i] = -1;
        for (int j = 1; j < i; ++j) {
          if (dis[j][i] > e[j])
            continue;
          double tmp = f[j] + dis[j][i] * 1.0 / s[j];
          if (f[i] < -1e-8 || tmp < f[i])
            f[i] = tmp;
        }
      }
      printf(" %.8lf", f[k]);
    }
    puts("");
  }
  return 0;
}
