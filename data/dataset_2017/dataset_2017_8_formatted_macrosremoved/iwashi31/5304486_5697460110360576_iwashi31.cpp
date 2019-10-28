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
using namespace std;

long long dx[4] = {1, 0, -1, 0};
long long dy[4] = {0, -1, 0, 1};

long long nextInt() {
  long long a;
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

template <class T> void inputVector(vector<T> &v, long long n) {
  v.resize(n);
  for (long long i = 0; i < v.size(); i++)
    cin >> v[i];
}

class Graph {
private:
  class Edge {
  public:
    long long to;
    long long cap;
    long long rev;
    Edge(long long to, long long cap, long long rev) {
      this->to = to;
      this->cap = cap;
      this->rev = rev;
    }
  };

  long long calcFlow(long long s, long long t, long long left) {
    if (s == t)
      return left;

    visited[s] = true;

    for (long long i = 0; i < (nextEdges[s].size()); i++) {
      Edge &edge = nextEdges[s][i];
      if (edge.cap == 0)
        continue;
      if (visited[edge.to])
        continue;
      long long flow = calcFlow(edge.to, t, min(left, edge.cap));
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
  Graph(long long n) {
    nextEdges.resize(n);
    visited.resize(n);
  }

  void addEdge(long long node, long long to, long long cap) {
    nextEdges[node].push_back(Edge(to, cap, nextEdges[to].size()));
    nextEdges[to].push_back(Edge(node, 0, nextEdges[node].size() - 1));
  }

  long long calcMaxFlow(long long s, long long t) {
    backUpNextEdges = nextEdges;

    long long ret = 0;
    while (true) {
      for (long long i = 0; i < (nextEdges.size()); i++)
        visited[i] = false;
      long long flow = calcFlow(s, t, INT_MAX);
      if (flow == 0)
        break;
      ret += flow;
    }

    nextEdges = backUpNextEdges;

    return ret;
  }
};

long long p[60][60];

signed main() {
  long long T;
  cin >> T;

  ofstream out("output-B-small.txt");
  for (long long loop = (1); loop <= (T); loop++) {
    long long N, P;
    cin >> N >> P;

    vector<long long> w;
    inputVector(w, N);

    for (long long i = 0; i < (N); i++)
      for (long long j = 0; j < (P); j++) {
        cin >> p[i][j];
      }

    long long ans = 0;
    if (N == 2) {
      Graph g(2 * P + 2);
      for (long long i = 0; i < (P); i++) {
        g.addEdge(0, i + 1, 1);
        g.addEdge(P + i + 1, 2 * P + 1, 1);
      }
      for (long long i = 0; i < (P); i++)
        for (long long j = 0; j < (P); j++) {
          for (long long k = (1); k <= (1000000); k++) {
            long long y = w[0] * k;
            long long x = p[0][i];
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
      for (long long i = 0; i < (P); i++) {
        for (long long k = (1); k <= (1000000); k++) {
          long long y = w[0] * k;
          long long x = p[0][i];
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
