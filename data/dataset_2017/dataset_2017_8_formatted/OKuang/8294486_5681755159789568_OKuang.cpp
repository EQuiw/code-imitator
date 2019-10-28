#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
const int maxn = 110;
int n, q;
LL ability[maxn], speed[maxn];
LL G[maxn][maxn];
double dist[maxn], ans[maxn];
bool vis[maxn];
bool Qvis[maxn];
queue<int> Q;
void spfa(int s) {
  while (!Q.empty())
    Q.pop();
  memset(Qvis, false, sizeof(Qvis));
  memset(vis, false, sizeof(vis));
  vis[s] = true;
  dist[s] = 0;
  Qvis[s] = true;
  Q.push(s);
  while (!Q.empty()) {
    int p = Q.front();
    Q.pop();
    Qvis[p] = false;
    for (int i = 1; i <= n; i++) {
      if (p == i)
        continue;
      if (G[p][i] == -1 || G[p][i] > ability[p])
        continue;
      double time = (double)G[p][i] / (double)speed[p];
      if (!vis[i] || dist[i] > dist[p] + time) {
        vis[i] = true;
        dist[i] = dist[p] + time;
        if (!Qvis[i]) {
          Q.push(i);
          Qvis[i] = true;
        }
      }
    }
  }
}
inline void solve() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++)
    scanf("%lld%lld", &ability[i], &speed[i]);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      scanf("%lld", &G[i][j]);
  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        if (i == j || G[i][k] == -1 || G[k][j] == -1)
          continue;
        if (G[i][j] == -1 || G[i][j] > G[i][k] + G[k][j])
          G[i][j] = G[i][k] + G[k][j];
      }
  int u, v;
  for (int i = 1; i <= q; i++) {
    scanf("%d%d", &u, &v);
    spfa(u);
    ans[i] = dist[v];
  }
  for (int i = 1; i < q; i++)
    printf("%.8f ", ans[i]);
  printf("%.8f\n", ans[q]);
}
int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int tcas = 1; tcas <= T; tcas++) {
    printf("Case #%d: ", tcas);
    solve();
  }
  return 0;
}
