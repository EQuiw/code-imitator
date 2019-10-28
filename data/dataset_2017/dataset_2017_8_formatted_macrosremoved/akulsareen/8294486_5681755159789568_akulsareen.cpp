#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const double INF = 1e18;
int maxd[MAXN], vel[MAXN];
long long int dist[MAXN][MAXN];
double min_time[MAXN][MAXN];
bool vis[MAXN];
int main() {
  int t;
  scanf("%d", &t);
  for (int case_num = 1; case_num <= t; ++case_num) {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i) {
      scanf("%d %d", &maxd[i], &vel[i]);
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        scanf("%lld", &dist[i][j]);
        if (dist[i][j] == -1)
          dist[i][j] = INF;
      }
      dist[i][i] = 0;
    }
    for (int k = 1; k <= n; ++k) {
      for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        min_time[i][j] = INF;
        vis[j] = false;
      }
      min_time[i][i] = 0;
      vis[i] = true;
      int curr_pos = i;
      for (int j = 1; j < n; ++j) {
        if (min_time[i][curr_pos] >= INF)
          break;
        for (int k = 1; k <= n; ++k) {
          if (dist[curr_pos][k] > maxd[curr_pos])
            continue;
          double curr_time =
              min_time[i][curr_pos] + (dist[curr_pos][k] * 1.0 / vel[curr_pos]);
          min_time[i][k] = min(min_time[i][k], curr_time);
        }
        curr_pos = -1;
        for (int k = 1; k <= n; ++k) {
          if (vis[k])
            continue;
          if (curr_pos == -1 || min_time[i][k] < min_time[i][curr_pos])
            curr_pos = k;
        }
        vis[curr_pos] = true;
      }
    }
    printf("Case #%d: ", case_num);
    for (int i = 0; i < q; ++i) {
      int u, v;
      scanf("%d %d", &u, &v);
      assert(min_time[u][v] < INF);
      printf("%.10lf ", min_time[u][v]);
    }
    printf("\n");
  }
  return 0;
}
