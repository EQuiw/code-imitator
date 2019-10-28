#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int mxd[N], sp[N];
int mat[N][N];

double dis[N];
bool done[N];

int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-small-attempt0.out", "w", stdout);
  int test;
  scanf("%d", &test);
  for (int _ = 1; _ <= test; _++) {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &mxd[i], &sp[i]);
    }

    memset(mat, 63, sizeof(mat));
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        int x;
        scanf("%d", &x);
        if (~x) {
          mat[i][j] = x;
        }
      }
    }
    for (int k = 1; k <= n; k++) {
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
          mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
        }
      }
    }

    printf("Case #%d:", _);
    while (q--) {
      int x, y;
      scanf("%d%d", &x, &y);
      for (int i = 1; i <= n; i++) {
        dis[i] = 1e60;
      }
      memset(done, 0, sizeof(done));
      priority_queue<pair<double, int>, vector<pair<double, int>>,
                     greater<pair<double, int>>>
          que;

      dis[x] = 0;
      que.push({dis[x], x});

      while (!que.empty()) {
        pair<double, int> u = que.top();
        que.pop();
        if (done[u.second]) {
          continue;
        }
        done[u.second] = true;
        for (int v = 1; v <= n; v++) {
          if (mat[u.second][v] <= mxd[u.second] &&
              dis[v] > dis[u.second] + mat[u.second][v] * 1.0 / sp[u.second]) {
            dis[v] = dis[u.second] + mat[u.second][v] * 1.0 / sp[u.second];
            que.push({dis[v], v});
          }
        }
      }
      printf(" %.10f", dis[y]);
    }
    puts("");
  }
  return 0;
}
