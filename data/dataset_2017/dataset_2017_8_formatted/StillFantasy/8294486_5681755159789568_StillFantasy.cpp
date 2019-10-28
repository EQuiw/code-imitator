#include <bits/stdc++.h>
using namespace std;

#define MAXN 110
#define INF 123456789123456LL
#define pii pair<double, int>
#define mp make_pair

struct Edge {
  int u, v;
  double w;
  Edge(int a, int b, double c) : u(a), v(b), w(c){};
};

struct Dijkstra {

  int n, m;
  vector<Edge> edges;
  vector<int> G[MAXN];
  bool done[MAXN];
  double d[MAXN];
  int p[MAXN];

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; i++)
      G[i].clear();
    edges.clear();
  }

  void AddEdge(int u, int v, double w) {
    G[u].push_back(edges.size());
    edges.push_back(Edge(u, v, w));
  }

  void dijkstra(int s) {
    priority_queue<pii, vector<pii>, greater<pii>> q;
    for (int i = 0; i < n; i++)
      d[i] = INF;
    d[s] = 0;
    memset(done, 0, sizeof(done));
    q.push(mp(0, s));
    while (!q.empty()) {
      int u = q.top().second;
      q.pop();
      if (done[u])
        continue;
      for (int i = 0; i < G[u].size(); i++) {
        Edge &e = edges[G[u][i]];
        if (d[e.v] > d[e.u] + e.w) {
          d[e.v] = d[e.u] + e.w;
          p[e.v] = G[u][i];
          q.push(mp(d[e.v], e.v));
        }
      }
    }
  }

} solver;

long long e[MAXN];
long long s[MAXN];
long long D[MAXN][MAXN];

int main() {
  int test, kase = 0;
  scanf("%d", &test);
  while (test--) {
    int n, op;
    scanf("%d%d", &n, &op);
    solver.init(n);
    for (int i = 0; i < n; i++) {
      scanf("%lld%lld", &e[i], &s[i]);
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%lld", &D[i][j]);
        if (D[i][j] == -1)
          D[i][j] = INF;
        if (i == j)
          D[i][j] = 0;
      }
    }

    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        if (D[i][j] != INF && i != j) {
          if (D[i][j] <= e[i]) {
            // cout << i << " " << j << " " << (double)D[i][j] / s[i] << endl;
            solver.AddEdge(i, j, (double)D[i][j] / s[i]);
          }
        }
    }

    printf("Case #%d:", ++kase);
    while (op--) {
      int st, ed;
      scanf("%d%d", &st, &ed);
      st--;
      ed--;
      solver.dijkstra(st);
      printf(" %.7lf", solver.d[ed]);
    }
    puts("");
  }
  return 0;
}