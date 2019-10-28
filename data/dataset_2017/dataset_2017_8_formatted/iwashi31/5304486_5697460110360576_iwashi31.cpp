#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define int long long
#define MOD7 1000000007
#define MOD9 1000000009

#define rep(i, n) for (int i = 0; i < (n); i++)
#define REP(i, a, n) for (int i = (a); i <= (n); i++)
#define all(a) (a).begin(), (a).end()

using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

int nextInt() {
  int a;
  cin >> a;
  return a;
}
char nextChar() {
  char a;
  cin >> a;
  return a;
}
double nextDouble() {
  double a;
  cin >> a;
  return a;
}
string nextString() {
  string a;
  cin >> a;
  return a;
}

template <class T> void inputVector(vector<T> &v, int n) {
  v.resize(n);
  for (int i = 0; i < v.size(); i++)
    cin >> v[i];
}

class Graph {
private:
  class Edge {
  public:
    int to;
    int cap;
    int rev;
    Edge(int to, int cap, int rev) {
      this->to = to;
      this->cap = cap;
      this->rev = rev;
    }
  };

  int calcFlow(int s, int t, int left) {
    if (s == t)
      return left;

    visited[s] = true;

    rep(i, nextEdges[s].size()) {
      Edge &edge = nextEdges[s][i];
      if (edge.cap == 0)
        continue;
      if (visited[edge.to])
        continue;
      int flow = calcFlow(edge.to, t, min(left, edge.cap));
      if (flow > 0) {
        edge.cap -= flow;
        nextEdges[edge.to][edge.rev].cap += flow;
        return flow;
      }
    }

    return 0;
  }

  vector<bool> visited;
  vector<vector<Edge>> nextEdges, backUpNextEdges;

public:
  Graph() {}
  Graph(int n) {
    nextEdges.resize(n);
    visited.resize(n);
  }

  void addEdge(int node, int to, int cap) {
    nextEdges[node].push_back(Edge(to, cap, nextEdges[to].size()));
    nextEdges[to].push_back(Edge(node, 0, nextEdges[node].size() - 1));
  }

  int calcMaxFlow(int s, int t) {
    backUpNextEdges = nextEdges;

    int ret = 0;
    while (true) {
      rep(i, nextEdges.size()) visited[i] = false;
      int flow = calcFlow(s, t, INT_MAX);
      if (flow == 0)
        break;
      ret += flow;
    }

    nextEdges = backUpNextEdges;

    return ret;
  }
};

int p[60][60];

signed main() {
  int T;
  cin >> T;

  ofstream out("output-B-small.txt");
  REP(loop, 1, T) {
    int N, P;
    cin >> N >> P;

    vector<int> w;
    inputVector(w, N);

    rep(i, N) rep(j, P) { cin >> p[i][j]; }

    int ans = 0;
    if (N == 2) {
      Graph g(2 * P + 2);
      rep(i, P) {
        g.addEdge(0, i + 1, 1);
        g.addEdge(P + i + 1, 2 * P + 1, 1);
      }
      rep(i, P) rep(j, P) {
        REP(k, 1, 1000000) {
          int y = w[0] * k;
          int x = p[0][i];
          if (x * 10 < y * 9)
            continue;
          if (x * 10 > y * 11)
            continue;

          y = w[1] * k;
          x = p[1][j];
          if (x * 10 < y * 9)
            continue;
          if (x * 10 > y * 11)
            continue;

          g.addEdge(i + 1, P + j + 1, 1);
          break;
        }
      }

      ans = g.calcMaxFlow(0, 2 * P + 1);
    } else {
      rep(i, P) {
        REP(k, 1, 1000000) {
          int y = w[0] * k;
          int x = p[0][i];
          if (x * 10 < y * 9)
            continue;
          if (x * 10 > y * 11)
            continue;

          ans++;
          break;
        }
      }
    }

    cout << "Case #" << loop << ": " << ans << endl;
    out << "Case #" << loop << ": " << ans << endl;
  }

  return 0;
}
