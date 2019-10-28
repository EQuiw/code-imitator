#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;
typedef long long ll;
const int maxn = 110;
struct state {
  int s, t, k;
  state() {}
  state(int s, int t, int k) : s(s), t(t), k(k) {}
};
int n, m;
ll d[maxn][maxn];
double f[maxn][maxn][maxn];
ll maxd[maxn], v[maxn];
bool inq[maxn][maxn][maxn];
void floyd() {
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      if (d[i][k] != -1)
        for (int j = 1; j <= n; ++j)
          if (d[k][j] != -1)
            if (d[i][j] == -1 || d[i][j] > d[i][k] + d[k][j])
              d[i][j] = d[i][k] + d[k][j];
}
void dp(int x) {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      f[x][i][j] = -1.0;
  static queue<state> q;
  while (!q.empty())
    q.pop();
  q.push(state(x, x, x));
  f[x][x][x] = 0;
  while (!q.empty()) {
    state now = q.front();
    q.pop();
    inq[now.s][now.t][now.k] = 0;
    // printf("f(%d %d %d) = %f\n", now.s, now.t, now.k,
    // f[now.s][now.t][now.k]);
    if (now.t != now.k) {
      if (f[now.s][now.t][now.t] < 0 ||
          f[now.s][now.t][now.t] > f[now.s][now.t][now.k]) {
        f[now.s][now.t][now.t] = f[now.s][now.t][now.k];
        if (!inq[now.s][now.t][now.t]) {
          inq[now.s][now.t][now.t] = 1;
          q.push(state(now.s, now.t, now.t));
        }
      }
    }
    for (int i = 1; i <= n; ++i)
      if (d[now.t][i] >= 0) {
        if (maxd[now.k] >= d[now.k][now.t] + d[now.t][i]) {
          if (f[now.s][i][now.k] < 0 ||
              f[now.s][i][now.k] >
                  f[now.s][now.t][now.k] + (double)d[now.t][i] / v[now.k]) {
            f[now.s][i][now.k] =
                f[now.s][now.t][now.k] + (double)d[now.t][i] / v[now.k];
            if (!inq[now.s][i][now.k]) {
              inq[now.s][i][now.k] = 1;
              q.push(state(now.s, i, now.k));
            }
          }
        }
      }
  }
}
int main() {
  // freopen("in.txt","r",stdin);
  // freopen("out2.txt","w",stdout);
  int T;
  cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
      cin >> maxd[i] >> v[i]; // scanf("%d%d", &maxd[i], &v[i]);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        cin >> d[i][j];
    // scanf("%d", &d[i][j]);
    for (int i = 1; i <= n; ++i)
      d[i][i] = 0;
    floyd();
    for (int i = 1; i <= n; ++i)
      dp(i);
    printf("Case #%d:", cas);
    for (int i = 1; i <= m; ++i) {
      int s, t;
      scanf("%d%d", &s, &t);
      double ans = -1;
      for (int i = 1; i <= n; ++i)
        if (f[s][t][i] >= 0) {
          if (ans < 0 || ans > f[s][t][i])
            ans = f[s][t][i];
        }
      printf(" %.8f", ans);
    }
    printf("\n");
  }
  return 0;
}
/*
1
3 1
2 3
2 4
4 4
-1 1 -1
-1 -1 1
-1 -1 -1
1 3
4 1
13 10
1 1000
10 8
5 5
-1 1 -1 -1
-1 -1 1 -1
-1 -1 -1 10
-1 -1 -1 -1
1 4
4 3
30 60
10 1000
12 5
20 1
-1 10 -1 31
10 -1 10 -1
-1 -1 -1 10
15 6 -1 -1
2 4
3 1
3 2
*/
