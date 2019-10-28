#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#define LL long long
using namespace std;
const LL INF = (LL)1e18;
const int maxn = (int)100 + 10;

int T_T;
int n, q;
int E[maxn], S[maxn];
int st[maxn], ed[maxn];
LL G[maxn][maxn];
double t[maxn][maxn], dis[maxn];
int inque[maxn];

void spfa(int st, double *time) {
  for (int i = 1; i <= n; i++)
    time[i] = 1e50;

  queue<int> Q;
  Q.push(st);
  inque[st] = 1;
  time[st] = 0.0;

  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    inque[u] = 0;
    for (int i = 1; i <= n; i++) {
      if (G[u][i] > E[u])
        continue;
      double ti = (double)G[u][i] / S[u];
      if (time[i] > ti + time[u]) {
        time[i] = ti + time[u];
        if (!inque[i])
          inque[i] = 1, Q.push(i);
      }
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("out-small.txt", "w", stdout);
#endif // LOCAL

  scanf("%d", &T_T);
  for (int cas = 1; cas <= T_T; cas++) {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
      scanf("%d%d", &E[i], &S[i]);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        scanf("%d", &G[i][j]);
        if (G[i][j] == -1)
          G[i][j] = INF;
      }
    for (int i = 0; i < q; i++)
      scanf("%d%d", &st[i], &ed[i]);

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        for (int k = 1; k <= n; k++)
          G[i][j] = min(G[i][j], G[i][k] + G[k][j]);

    for (int i = 1; i <= n; i++)
      spfa(i, t[i]);

    printf("Case #%d:", cas);
    for (int i = 0; i < q; i++) {
      printf(" %.9lf", t[st[i]][ed[i]]);
    }
    puts("");
  }
  return 0;
}
