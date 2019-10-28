#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-small-attempt0.out", "w", stdout);

  int T;
  scanf("%d", &T);
  for (int cn = 1; cn <= T; ++cn) {
    int N, Q;
    scanf("%d%d", &N, &Q);
    vector<long long> horse_dist(N), horse_speed(N);
    vector<vector<long long>> graph(N, vector<long long>(N, 0));
    for (int i = 0; i < N; ++i)
      scanf("%I64d%I64d", &horse_dist[i], &horse_speed[i]);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        scanf("%I64d", &graph[i][j]);

    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j) {
        if (graph[j][i] == -1)
          continue;
        for (int k = 0; k < N; ++k) {
          if (graph[i][k] == -1)
            continue;
          if (graph[j][k] == -1 || graph[j][k] > graph[j][i] + graph[i][k])
            graph[j][k] = graph[j][i] + graph[i][k];
        }
      }

    printf("Case #%d:", cn);
    double MAX = 1e20;

    for (int i = 0; i < Q; ++i) {
      vector<double> arrive_time(N, 2 * MAX);
      int u, v;
      scanf("%d%d", &u, &v);
      u--, v--;

      priority_queue<pair<double, int>> PQ;
      PQ.push({0, u});
      while (!PQ.empty()) {
        pair<double, int> now = PQ.top();
        PQ.pop();
        if (arrive_time[now.second] < MAX)
          continue;

        arrive_time[now.second] = -now.first;
        if (now.second == v) {
          printf(" %.10lf", -now.first);
          break;
        }
        for (int i = 0; i < N; ++i) {
          if (graph[now.second][i] == -1 || i == now.second)
            continue;
          if (graph[now.second][i] > horse_dist[now.second])
            continue;

          double time_i = -arrive_time[now.second] -
                          graph[now.second][i] * 1.0 / horse_speed[now.second];
          PQ.push({time_i, i});
        }
      }
    }
    printf("\n");
  }
}