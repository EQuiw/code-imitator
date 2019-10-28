#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

long long gra[100 + 1][100 + 1];
int lim[100 + 1], spd[100 + 1], vis[100 + 1];
double dis[100 + 1];
int n, q;

double dijkstra(int s, int e) {
  int i, j, u;
  double newd;
  memset(vis, 0, sizeof(vis));
  fill(dis + 1, dis + n + 1, 1000000000000000000LL);
  dis[s] = 0.0;
  for (i = 1; i <= n; i++) {
    newd = 1000000000000000000LL;
    u = -1;
    for (j = 1; j <= n; j++) {
      if ((vis[j] == 0) && (newd > dis[j])) {
        newd = dis[j];
        u = j;
      }
    }
    if (u == -1) {
      break;
    }
    vis[u] = 1;
    for (j = 1; j <= n; j++) {
      if ((lim[u] >= gra[u][j]) &&
          (dis[j] > dis[u] + 1.0 * gra[u][j] / spd[u])) {
        dis[j] = dis[u] + 1.0 * gra[u][j] / spd[u];
      }
    }
  }
  return dis[e];
}

int main() {
  freopen("C-small-attempt1.in", "r", stdin);
  freopen("C-small-attempt1.out", "w", stdout);
  int c, t, i, j, k, u, v;
  scanf("%d", &t);
  for (c = 0; c < t; c++) {
    scanf("%d %d", &n, &q);
    for (i = 1; i <= n; i++) {
      scanf("%d %d", &lim[i], &spd[i]);
    }
    for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++) {
        scanf("%lld", &gra[i][j]);
        if (gra[i][j] == -1) {
          gra[i][j] = 1000000000000000000LL;
        }
      }
    }
    for (k = 1; k <= n; k++) {
      for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
          gra[i][j] = min(gra[i][j], gra[i][k] + gra[k][j]);
        }
      }
    }
    printf("Case #%d:", c + 1);
    for (i = 0; i < q; i++) {
      scanf("%d %d", &u, &v);
      printf(" %.9f", dijkstra(u, v));
    }
    printf("\n");
  }
  return 0;
}
