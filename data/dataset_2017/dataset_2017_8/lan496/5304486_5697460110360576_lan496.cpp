#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define ALL(x) (x).begin(), (x).end()

typedef long long ll;
typedef long double ld;

const int INF = 1e9;
const ld EPS = 1e-8;

typedef int Weight;
typedef int Flow;

struct Edge {
  int src, dest, rev;
  Flow cap;
  Weight cost;
  bool operator < (const Edge &rhs) const {
    return cost > rhs.cost;
  }
  Edge(int s, int d) : src(s), dest(d) { ; }
  Edge(int s, int d, Weight c) : src(s), dest(d), cost(c) { ; }
  Edge(int s, int d, int r, Flow cp, Weight cst) : src(s), dest(d), rev(r), cap(cp), cost(cst) { ; }
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;
typedef vector<Weight> Array;
typedef vector<Array> Matrix;

void add_edge(Graph &g, int src, int dest, Flow cap) {
  g[src].push_back((Edge) { src, dest, (int)g[dest].size(), cap, 0 });
  g[dest].push_back((Edge) { dest, src, (int)g[src].size() - 1, 0, 0 });
}

Flow dfs(Graph &g, vector<bool> &used, int v, int t, Flow f) {
  if (v == t) return f;
  used[v] = true;
  for (Edge &e : g[v]) {
    if (!used[e.dest] && e.cap > 0) {
      Flow d = dfs(g, used, e.dest, t, min(f, e.cap));
      if (d > 0) {
        e.cap -= d;
        g[e.dest][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

Flow ford_fulkerson(Graph &g, int s, int t) {
  Flow flow = 0;
  for (;;) {
    vector<bool> used(g.size(), false);
    Flow f = dfs(g, used, s, t, INF);
    if (f == 0) return flow;
    flow += f;
  }
}

bool check(int Ri, int Qij, int k) {
  if(9 * k * Ri > 10 * Qij) return false;
  if(10 * Qij > 11 * k * Ri) return false;
  return true;
}

pair<int,int> f(int Ri, int Qij) {
  int a = (ld)(Qij) / (ld)(1.1 * Ri);
  int b = (ld)(Qij) / (ld)(0.9 * Ri);
  if(!check(Ri, Qij, a)) ++a;
  if(check(Ri, Qij, b + 1)) ++b;
  return make_pair(a, b);
}

int main(){
  int T;
  cin >> T;
  REP(t,T) {
    int N, P;
    cin >> N >> P;
    vector<int> R(N);
    vector<vector<int>> Q(N, vector<int> (P));
    REP(i,N) cin >> R[i];
    REP(i,N)REP(j,P) cin >> Q[i][j];

    vector<vector<pair<int,int>>> tmp(N, vector<pair<int,int>> (P));
    REP(i,N)REP(j,P) tmp[i][j] = f(R[i], Q[i][j]);

    Graph g(N * P + 2);
    int source = N * P;
    int sink = N * P + 1;
    REP(j,P) {
      if(tmp[0][j].first > tmp[0][j].second) continue;
      add_edge(g, source, j, 1);
    }
    REP(i,N - 1)REP(j,P)REP(k,P) {
      if(tmp[i][j].first > tmp[i][j].second) continue;
      if(tmp[i + 1][k].first > tmp[i + 1][k].second) continue;
      if(max(tmp[i][j].first, tmp[i + 1][k].first) <= min(tmp[i][j].second, tmp[i + 1][k].second)) {
        add_edge(g, i * P + j, (i + 1) * P + k, 1);
      }
    }
    REP(j,P) {
      if(tmp[N - 1][j].first > tmp[N - 1][j].second) continue;
      add_edge(g, (N - 1) * P + j, sink, 1);
    }

    /*
    REP(i,N) {
      REP(j,P) cout << "(" << tmp[i][j].first << "," << tmp[i][j].second << ")";
      cout << endl;
    }

    REP(i,N * P + 2) {
      cout << i << ": ";
      for(Edge e: g[i]) {
        if(!e.cap) continue;
        cout << e.dest << ",";
      }
      cout << endl;
    }
    */

    int res = ford_fulkerson(g, source, sink);

    cout << "Case #" << t + 1 << ": " << res << endl;
  }
  return 0;
}

