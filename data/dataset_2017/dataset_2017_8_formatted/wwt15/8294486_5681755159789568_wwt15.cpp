#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

const int N = 105;
const int inf = int(1e9) + 7;
const db oo = 1. / 0;

int n, q;
int E[N], S[N];
int d[N][N];
db dist[N][N];

int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C.out", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int Case = 1; Case <= T; Case++) {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
      scanf("%d%d", &E[i], &S[i]);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        scanf("%d", &d[i][j]);
        if (d[i][j] == -1)
          d[i][j] = inf;
        if (i == j)
          d[i][j] = 0;
      }
    for (int k = 1; k <= n; k++)
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        dist[i][j] = E[i] >= d[i][j] ? (db)d[i][j] / S[i] : oo;
    for (int k = 1; k <= n; k++)
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    printf("Case #%d:", Case);
    while (q--) {
      int u, v;
      scanf("%d%d", &u, &v);
      printf(" %.10lf", dist[u][v]);
    }
    printf("\n");
  }
}
