#include <bits/stdc++.h>

using namespace std;

//#define LARGE

const int N = 105;

int n, q;
long long dis[N][N], e[N], s[N];
double dp[N][N];

void floyd() {
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (dis[i][k] != -1 && dis[k][j] != -1 &&
            (dis[i][j] == -1 || dis[i][j] > dis[i][k] + dis[k][j]))
          dis[i][j] = dis[i][k] + dis[k][j];
}

double bfs(const int &from, const int &to) {
  deque<pair<int, int>> de;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      dp[i][j] = 1e18;
  for (int i = 0; i < n; ++i)
    if (i != from && dis[from][i] != -1 && e[from] >= dis[from][i]) {
      dp[from][i] = 1.0 * dis[from][i] / s[from];
      de.push_back(make_pair(from, i));
    }
  while (!de.empty()) {
    int horse = de.front().first;
    int u = de.front().second;
    //    printf("%d %d %lf\n", horse, u, dp[horse][u]);
    de.pop_front();
    for (int i = 0; i < n; ++i) {
      if (dis[u][i] == -1)
        continue;
      int remain = e[horse] - dis[horse][u];
      if (remain >= dis[u][i]) {
        if (dp[horse][i] > dp[horse][u] + 1.0 * dis[u][i] / s[horse]) {
          dp[horse][i] = dp[horse][u] + 1.0 * dis[u][i] / s[horse];
          de.push_back(make_pair(horse, i));
        }
      }
      if (e[u] >= dis[u][i]) {
        if (dp[u][i] > dp[horse][u] + 1.0 * dis[u][i] / s[u]) {
          dp[u][i] = dp[horse][u] + 1.0 * dis[u][i] / s[u];
          de.push_back(make_pair(u, i));
        }
      }
    }
  }
  double ret = 1e18;
  for (int i = 0; i < n; ++i)
    ret = min(ret, dp[i][to]);
  return ret;
}

int main() {

  freopen("C-small.in", "r", stdin);
  freopen("C-small.out", "w", stdout);

  int T;
  scanf("%d", &T);
  for (int Case = 1; Case <= T; ++Case) {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; ++i)
      scanf("%d %d", &e[i], &s[i]);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        scanf("%lld", &dis[i][j]);
    floyd();
    printf("Case #%d:", Case);
    int u, v;
    for (int i = 0; i < q; ++i) {
      scanf("%d %d", &u, &v);
      printf(" %.9lf", bfs(u - 1, v - 1));
    }
    printf("\n");
  }
  return 0;
}
