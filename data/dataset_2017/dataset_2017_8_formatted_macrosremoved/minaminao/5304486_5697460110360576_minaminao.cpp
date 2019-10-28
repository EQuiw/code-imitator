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

using Weight = long long;
using Flow = long long;
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

struct Dinic {
  long long n, s, t;
  vector<long long> level, prog, que;
  vector<vector<Flow>> cap, flow;
  vector<vector<long long>> g;
  Flow inf;
  Dinic(const Graph &graph)
      : n(graph.size()), cap(n, vector<Flow>(n)), flow(n, vector<Flow>(n)),
        g(n, vector<long long>()), inf(numeric_limits<Flow>::max() / 8) {
    for (long long i = 0; i < n; i++) {
      for (auto &e : graph[i]) {
        long long u = e.s, v = e.d;
        Flow c = e.c;
        cap[u][v] += c;
        cap[v][u] += c;
        flow[v][u] += c;
        g[u].push_back(v);
        g[v].push_back(u);
      }
    }
  }
  inline Flow residue(long long u, long long v) {
    return cap[u][v] - flow[u][v];
  }
  Flow solve(long long s_, long long t_) {
    this->t = t_, this->s = s_;
    que.resize(n + 1);
    Flow res = 0;
    while (levelize()) {
      prog.assign(n, 0);
      res += augment(s, inf);
    }
    return res;
  }
  bool levelize() {
    long long l = 0, r = 0;
    level.assign(n, -1);
    level[s] = 0;
    que[r++] = s;
    while (l != r) {
      long long v = que[l++];
      if (v == t)
        break;
      for (const long long &d : g[v])
        if (level[d] == -1 && residue(v, d) != 0) {
          level[d] = level[v] + 1;
          que[r++] = d;
        }
    }
    return level[t] != -1;
  }
  Flow augment(long long v, Flow lim) {
    Flow res = 0;
    if (v == t)
      return lim;
    for (long long &i = prog[v]; i < (long long)g[v].size(); i++) {
      const long long &d = g[v][i];
      if (residue(v, d) == 0 || level[v] >= level[d])
        continue;
      const Flow aug = augment(d, min(lim, residue(v, d)));
      flow[v][d] += aug;
      flow[d][v] -= aug;
      res += aug;
      lim -= aug;
      if (lim == 0)
        break;
    }
    return res;
  }
};

signed main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.txt", "w", stdout);
  // freopen("in.txt", "r", stdin);
  ////freopen("out.txt", "w", stdout);
  long long T;
  cin >> T;
  for (long long t = 0; t < T; t++) {
    long long N, P;
    cin >> N >> P;
    vector<long long> R(N);
    for (long long i = (0); i < (N); i++) {
      cin >> R[i];
    }
    vector<vector<long long>> Q(N, vector<long long>(P));
    for (long long i = (0); i < (N); i++)
      for (long long j = (0); j < (P); j++) {
        cin >> Q[i][j];
      }

    if (N == 1) {
      long long ans = 0;
      for (long long i = (0); i < (P); i++) {
        long long a = ceil(Q[0][i] * 100 / 110.0 / R[0]);
        long long b = Q[0][i] * 100 / 90.0 / R[0];
        if (a <= b)
          ans++;
      }
      cout << "Case #" << t + 1 << ": " << ans << endl;
      continue;
    }

    sort(begin(Q[0]), end(Q[0]));
    sort(begin(Q[1]), end(Q[1]));
    ;
    long long ans = 0;
    do {
      long long cnt = 0;
      for (long long i = (0); i < (P); i++) {
        long long a = ceil(Q[0][i] * 100 / 110.0 / R[0]);
        long long b = Q[0][i] * 100 / 90.0 / R[0];
        long long c = ceil(Q[1][i] * 100 / 110.0 / R[1]);
        long long d = Q[1][i] * 100 / 90.0 / R[1];
        // dump(a, b, c, d);
        if (a <= d && c <= b)
          cnt++;
      }
      chmax(ans, cnt);
    } while (next_permutation(begin(Q[1]), end(Q[1])));

    cout << "Case #" << t + 1 << ": " << ans << endl;
  }
  return 0;
}
