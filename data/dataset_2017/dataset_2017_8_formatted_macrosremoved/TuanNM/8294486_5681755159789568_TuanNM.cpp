#include <bits/stdc++.h>

using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3f;
const int N = 110;

int n, q;
long long dist[N][N];
int e[N], ss[N];
struct pnt {
  double a;
  int b;
  pnt(double _a = 0.0, int _b = 0) {
    a = _a;
    b = _b;
  }
  bool operator<(const pnt &op) const {
    if (a != op.a)
      return a > op.a;
    return b < op.b;
  }
};

priority_queue<pnt> qq;
vector<int> g[N];
double dd[N];

double solve(int s, int t) {
  while (!qq.empty())
    qq.pop();
  for (int i = 0; i < n; ++i)
    dd[i] = INF;
  dd[s] = 0.0;
  qq.push(pnt(dd[s], s));
  while (!qq.empty()) {
    double du = qq.top().a;
    int u = qq.top().b;
    qq.pop();
    if (du > dd[u])
      continue;
    for (int i = 0; i < (int)(g[u]).size(); ++i) {
      int v = g[u][i];
      double cost = (double)dist[u][v] / ss[u];

      if (e[u] >= dist[u][v] && dd[v] > dd[u] + cost) {
        dd[v] = dd[u] + cost;
        qq.push(pnt(dd[v], v));
      }
    }
  }
  return dd[t];
}

int main() {
  // freopen("A.inp", "r", stdin);
  // freopen("A.out", "w", stdout);
  int tests;
  scanf("%d", &tests);
  for (int test = 1; test <= tests; ++test) {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; ++i)
      scanf("%d %d", e + i, ss + i);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        scanf("%I64d", &dist[i][j]);
        if (dist[i][j] == -1)
          dist[i][j] = INF;
      }
    }
    for (int k = (0), _b = (n); k < _b; ++k) {
      for (int i = (0), _b = (n); i < _b; ++i) {
        for (int j = (0), _b = (n); j < _b; ++j)
          if (dist[i][j] > dist[i][k] + dist[k][j]) {
            dist[i][j] = dist[i][k] + dist[k][j];
          }
      }
    }
    for (int i = (0), _b = (n); i < _b; ++i) {
      g[i].clear();
      for (int j = (0), _b = (n); j < _b; ++j)
        if (dist[i][j] < INF) {
          g[i].push_back(j);
        }
    }
    printf("Case #%d:", test);
    for (int i = 0; i < q; ++i) {
      int s, t;
      cin >> s >> t;
      s--;
      t--;
      double ans = solve(s, t);
      printf(" %.07lf", ans);
    }
    printf("\n");
  }
  return 0;
}
