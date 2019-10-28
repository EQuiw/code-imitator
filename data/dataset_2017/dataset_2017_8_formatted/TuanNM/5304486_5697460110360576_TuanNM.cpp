#include <bits/stdc++.h>
#define TR(c, it) for (__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define FOR(i, a, b) for (int i = (a), _b = (b); i < _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define FORE(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define SZ(c) (int)(c).size()

using namespace std;

const int N = 100010;
const int INF = (int)1e9;

class Dinic {
public:
  struct Edge {
    int from, to, cap, flow;
    Edge(int _from = -1, int _to = -1, int _cap = 0, int _flow = 0)
        : from(_from), to(_to), cap(_cap), flow(_flow) {}
  };
  int n;
  vector<vector<int>> g;
  vector<vector<int>::iterator> work;
  vector<Edge> edges;
  vector<int> level;

  void init(int _n) {
    n = _n;
    g.assign(_n, vector<int>());
    work.assign(_n, vector<int>::iterator());
    edges.clear();
    level.resize(_n);
  }
  void addEdge(int u, int v, int cap, bool twoWay) {
    g[u].push_back((int)edges.size());
    edges.push_back(Edge(u, v, cap, 0));
    g[v].push_back((int)edges.size());
    edges.push_back(Edge(v, u, (twoWay == true) ? cap : 0, 0));
  }

  void resetFlows() {
    for (int i = 0; i < (int)edges.size(); ++i)
      edges[i].flow = 0;
  }

  bool bfs(int s, int t) {
    level = vector<int>(n, -1);
    queue<int> q;
    q.push(s);
    level[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      TR(g[u], it) {
        int e = *it;
        int v = edges[e].to;
        if (level[v] == -1 && edges[e].flow < edges[e].cap) {
          level[v] = level[u] + 1;
          q.push(v);
        }
      }
    }
    return (level[t] != -1);
  }

  int dfs(int s, int t, int f) {
    if (s == t)
      return f;
    for (vector<int>::iterator &e = work[s]; e != g[s].end(); ++e) {
      int v = edges[*e].to;
      if (level[v] == level[s] + 1 && edges[*e].flow < edges[*e].cap) {
        int d = dfs(v, t, min(f, edges[*e].cap - edges[*e].flow));
        if (d > 0) {
          edges[*e].flow += d;
          edges[*e ^ 1].flow -= d;
          return d;
        }
      }
    }
    return 0;
  }

  int maxFlow(int s, int t) {
    int ret = 0;
    while (bfs(s, t)) {
      for (int i = 0; i < n; ++i)
        work[i] = g[i].begin();
      for (int d; (d = dfs(s, t, numeric_limits<int>::max())) != 0; ret += d)
        ;
    }
    return ret;
  }

} netWork;

int n, p;
int a[N];
int b[55][55];

int numMax(double a, double b) {
  double c = a * 9.0 / 10.0;
  int ret = (int)(b / c);
  double d = a * 11 / 10;
  for (; ret >= 0; ret--) {
    if (1.0 * ret * c <= b && b <= 1.0 * ret * d)
      return ret;
    if (1.0 * ret * d < b)
      return 0;
  }
}

int numMin(double a, double b) {
  double c = a * 9.0 / 10.0;
  double d = a * 11 / 10;
  int ret = (int)(b / d);

  for (; ret < INF; ret++) {
    if (1.0 * ret * c <= b && b <= 1.0 * ret * d)
      return ret;
    if (1.0 * ret * c > b)
      return 0;
  }
}

int main() {
  // freopen("B.inp", "r", stdin);
  // freopen("B.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int nTest;
  cin >> nTest;
  for (int test = 1; test <= nTest; ++test) {
    cout << "Case #" << test << ": ";
    cin >> n >> p;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    FORE(i, 1, n) { FORE(j, 1, p) cin >> b[i][j]; }

    int s = 0, t = n * p + 1;
    netWork.init(t + 1);
    for (int i = 1; i <= p; ++i) {
      int a1 = numMin(a[1], b[1][i]);
      if (a1 > 0)
        netWork.addEdge(s, i, 1, false);
      if (n == 2) {
        for (int j = 1; j <= p; ++j) {
          int aa = numMin(a[1], b[1][i]);
          int bb = numMax(a[1], b[1][i]);
          int cc = numMin(a[2], b[2][j]);
          int dd = numMax(a[2], b[2][j]);
          aa = max(aa, cc);
          bb = min(bb, dd);
          if (aa <= bb && ((aa == 0 && bb > 0) || aa > 0))
            netWork.addEdge(i, j + p, 1, false);
        }
        int a2 = numMin(a[2], b[2][i]);
        if (a2 > 0)
          netWork.addEdge(i + p, t, 1, false);
      } else {
        if (a1 > 0)
          netWork.addEdge(i, t, 1, false);
      }
    }

    int ans = netWork.maxFlow(s, t);
    cout << ans << endl;
  }

  // cout << numMin(300, 809);// << " " << numMax(300, 809) << endl;

  return 0;
}
