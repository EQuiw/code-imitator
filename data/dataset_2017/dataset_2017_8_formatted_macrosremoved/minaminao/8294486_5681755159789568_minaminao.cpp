#include "bits/stdc++.h"
using namespace std;
const long long INF =
    sizeof(long long) == sizeof(long long) ? 0x3f3f3f3f3f3f3f3fLL : 0x3f3f3f3f;
const long long MOD = (long long)(1e9) + 7;
template <class T> bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
template <class T> bool chmin(T &a, const T &b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}

using Weight = double;
using Flow = double;
struct Edge {
  long long s, d;
  Weight w;
  Flow c;
  Edge(){};
  Edge(long long s, long long d, Weight w = 1) : s(s), d(d), w(w), c(w){};
};
bool operator<(const Edge &e1, const Edge &e2) { return e1.w < e2.w; }
bool operator>(const Edge &e1, const Edge &e2) { return e2 < e1; }
inline ostream &operator<<(ostream &os, const Edge &e) {
  return (os << '(' << e.s << ", " << e.d << ", " << e.w << ')');
}

using Edges = vector<Edge>;
using Graph = vector<Edges>;
using Array = vector<Weight>;
using Matrix = vector<Array>;

void add_arc(Graph &g, long long s, long long d, Weight w = 1) {
  g[s].emplace_back(s, d, w);
}
void add_edge(Graph &g, long long a, long long b, Weight w = 1) {
  add_arc(g, a, b, w);
  add_arc(g, b, a, w);
}

vector<long long> dijkstra(const Graph &g, long long s, Array &dist) {
  long long n = g.size();
  assert(s < n);
  enum { WHITE, GRAY, BLACK };
  vector<long long> color(n, WHITE);
  color[s] = GRAY;
  vector<long long> prev(n, -1);
  dist.assign(n, INF);
  dist[s] = 0;
  using State = tuple<Weight, long long, long long>;
  priority_queue<State, vector<State>, greater<State>> pq;
  pq.emplace(0, s, -1);
  while (pq.size()) {
    Weight d;
    long long v, u;
    tie(d, v, u) = pq.top();
    pq.pop();
    if (dist[v] < d)
      continue;
    color[v] = BLACK;
    prev[v] = u;
    for (auto &e : g[v]) {
      if (color[e.d] == BLACK)
        continue;
      if (dist[e.d] > dist[v] + e.w) {
        dist[e.d] = dist[v] + e.w;
        pq.emplace(dist[e.d], e.d, v);
        color[e.d] = GRAY;
      }
    }
  }
  return prev;
}

void all_pairs_shortest_paths_by_dijkstra(const Graph &g, Matrix &dists) {
  long long n = g.size();
  dists.resize(n);
  for (long long i = 0; i < n; i++)
    dijkstra(g, i, dists[i]);
}

signed main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-small-attempt0.txt", "w", stdout);
  // freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
  long long T;
  cin >> T;
  cout << fixed << setprecision(10);
  for (long long t = 0; t < T; t++) {
    long long N, Q;
    cin >> N >> Q;
    Graph g(N);
    vector<double> E(N), S(N);
    for (long long i = (0); i < (N); i++) {
      cin >> E[i] >> S[i];
    }
    for (long long i = (0); i < (N); i++)
      for (long long j = (0); j < (N); j++) {
        long long D;
        cin >> D;
        if (D == -1)
          continue;
        add_arc(g, i, j, D);
      }
    vector<long long> U(Q), V(Q);
    for (long long i = (0); i < (Q); i++) {
      cin >> U[i] >> V[i];
      U[i]--, V[i]--;
    }
    Matrix D;
    all_pairs_shortest_paths_by_dijkstra(g, D);
    Graph g2(N);
    for (long long i = (0); i < (N); i++) {
      for (long long j = (0); j < (N); j++) {
        if (i == j)
          continue;
        if (D[i][j] > E[i])
          continue;
        add_arc(g2, i, j, D[i][j] / S[i]);
      }
    }
    Matrix D2;
    all_pairs_shortest_paths_by_dijkstra(g2, D2);
    cout << "Case #" << t + 1 << ":";
    for (long long i = (0); i < (Q); i++) {
      cout << " " << D2[U[i]][V[i]];
    }
    cout << endl;
  }
  return 0;
}
