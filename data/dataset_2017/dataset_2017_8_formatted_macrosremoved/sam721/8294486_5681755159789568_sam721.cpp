#include <bits/stdc++.h>

using namespace std;
double D[110][110];
double adj[110][110];
int n, q, t;
double s[110];
double d[110];
class edge {
public:
  int u, v;
  double dist;
  edge(int a, int b, double c) {
    u = a;
    v = b;
    dist = c;
  }
};
class node {
public:
  int n;
  double t, d;
  node() {}
  node(int a, double b, double c) {
    n = a;
    t = b;
    d = c;
  }
  bool operator<(const node &other) const { return other.t < t; }
};
bool V[110];
vector<edge> g[110];
double dd[110];
void dijkstra(int h) {
  priority_queue<node> pq;
  pq.push(node(h, 0.0, 0.0));
  for (int i = 0; i < n; i++)
    dd[i] = 1e100;
  dd[h] = 0.0;
  memset(V, false, sizeof(V));
  while (!pq.empty()) {
    node aux = pq.top();
    pq.pop();
    int cur = aux.n;
    double dist = aux.d;
    double tt = aux.t;
    if (dist > d[h])
      continue;
    if (V[cur])
      continue;
    V[cur] = true;
    for (int i = 0; i < (int)g[cur].size(); i++) {
      int next = g[cur][i].v;
      double nd = dist + g[cur][i].dist;
      double nt = tt + g[cur][i].dist / s[h];
      if (nt < dd[next]) {
        dd[next] = nt;
        pq.push(node(next, nt, nd));
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (V[i])
      D[h][i] = dd[i];
  }
}

void fw() {
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
      }
    }
  }
}
int main() {
  scanf("%d", &t);
  for (int c = 1; c <= t; c++) {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        D[i][j] = 1e100;
      }
    }
    for (int i = 0; i < n; i++) {
      scanf("%lf %lf", &d[i], &s[i]);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%lf", &adj[i][j]);
        if (adj[i][j] != -1)
          g[i].push_back(edge(i, j, adj[i][j]));
      }
    }
    for (int i = 0; i < n; i++) {
      dijkstra(i);
    }
    fw();
    printf("Case #%d: ", c);
    for (int i = 0; i < q; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      printf("%s%.10lf", (i == 0) ? ("") : (" "), D[x - 1][y - 1]);
    }
    printf("\n");
    for (int i = 0; i <= n; i++)
      g[i].clear();
  }

  return 0;
}
