#include <algorithm>
#include <complex>
#include <cstdarg>
#include <cstdio>
#include <functional>
#include <iomanip>
#include <istream>
#include <limits>
#include <map>
#include <numeric>
#include <ostream>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

namespace caide {

typedef long long ll;

template <typename T> vector<vector<T>> makeVector(int n, int m) {
  return vector<vector<T>>(n, vector<T>(m));
}

struct GraphEdge {
  int id, to;
};

class GraphV {
public:
  explicit GraphV(int numVertices = 0);
  GraphV(const GraphV &) = default;

  const std::vector<GraphEdge> &outEdges(int fromVertex) const;

  int numVertices() const;

  int addEdge(int from, int to);

private:
  std::vector<std::vector<GraphEdge>> edges;
  int edgeId;
};

template <typename Graph, typename D>
std::vector<D> dijkstra(const Graph &g, const std::vector<D> &len,
                        const int source, const int target = -1,
                        const std::vector<bool> *haveEdge = nullptr,
                        const std::vector<D> *potentials = nullptr,
                        std::vector<int> *prevVertex = nullptr,
                        std::vector<int> *prevEdge = nullptr);

} // namespace caide

namespace caide {

template <typename Graph, typename D>
std::vector<D> dijkstra(const Graph &g, const std::vector<D> &len,
                        const int source, const int target /*= -1*/,
                        const std::vector<bool> *haveEdge /*= nullptr*/,
                        const std::vector<D> *potentials /*= nullptr*/,
                        std::vector<int> *prevVertex /*= nullptr*/,
                        std::vector<int> *prevEdge /*= nullptr*/) {
  static const D INF = std::numeric_limits<D>::max();

  const int n = g.numVertices();

  std::vector<D> zeros(n, (D)0);
  const std::vector<D> &h = potentials ? *potentials : zeros;

  if (prevVertex) {
    prevVertex->clear();
    prevVertex->resize(n, -1);
  }

  if (prevEdge) {
    prevEdge->clear();
    prevEdge->resize(n, -1);
  }

  std::vector<D> d(n, INF);
  std::set<std::pair<D, int>> queue;

  d[source] = 0;
  queue.insert(std::make_pair((D)0, source));

  while (!queue.empty()) {
    std::pair<D, int> p = *queue.begin();
    queue.erase(queue.begin());
    const int s = p.second;
    if (s == target)
      break;
    for (const auto &edge : g.outEdges(s)) {
      const int e = edge.id;
      if (haveEdge && !((*haveEdge)[e]))
        continue;
      const int t = edge.to;
      if (d[t] > d[s] + len[e] + h[t] - h[s]) {
        queue.erase(std::make_pair(d[t], t));
        d[t] = d[s] + len[e] + h[t] - h[s];
        queue.insert(std::make_pair(d[t], t));
        if (prevVertex)
          (*prevVertex)[t] = s;
        if (prevEdge)
          (*prevEdge)[t] = e;
      }
    }
  }

  return d;
}

} // namespace caide

using namespace caide;

// Powered by caide (code generator, tester, and library code inliner)

class Solution {
public:
  const ll INF = (ll)1e12;
  void solve(std::istream &in, std::ostream &out) {
    int T;
    in >> T;
    for (int test = 1; test <= T; ++test) {
      int N, Q;
      in >> N >> Q;
      vector<ll> hdist(N), hspeed(N);
      for (int i = 0; i < N; ++i)
        in >> hdist[i] >> hspeed[i];
      auto d = makeVector<ll>(N, N);
      for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
          in >> d[i][j];
          if (d[i][j] == -1)
            d[i][j] = INF;
        }
      for (int i = 0; i < N; ++i)
        d[i][i] = 0;

      for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
          for (int j = 0; j < N; ++j)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

      GraphV g(N * N);
      vector<double> edge;
      for (int city = 0; city < N; ++city)
        for (int horse = 0; horse < N; ++horse) {
          ll curDist = d[horse][city];
          if (curDist > hdist[horse])
            continue;

          int vcur = city * N + horse;
          if (horse != city) {
            g.addEdge(vcur, city * N + city);
            edge.push_back(0);
          }

          for (int i = 0; i < N; ++i)
            if (d[city][i] != INF && d[city][i] + curDist <= hdist[horse]) {
              g.addEdge(vcur, i * N + horse);
              edge.push_back((double)d[city][i] / hspeed[horse]);
            }
        }

      out << "Case #" << test << ":";
      while (Q--) {
        int u, v;
        in >> u >> v;
        --u;
        --v;
        auto dist = dijkstra(g, edge, u * N + u);
        double res = numeric_limits<double>::max();
        for (int i = 0; i < N; ++i)
          res = min(res, dist[v * N + i]);
        out << " " << res;
      }
      out << "\n";
    }
  }
};

void solve(std::istream &in, std::ostream &out) {
  out << std::setprecision(12);
  Solution solution;
  solution.solve(in, out);
}

#include <fstream>
#include <iostream>

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);

  istream &in = cin;

  ostream &out = cout;

  solve(in, out);
  return 0;
}

#include <cstdlib>

namespace caide {

GraphV::GraphV(int numVertices) : edges(numVertices), edgeId(0) {}

const vector<GraphEdge> &GraphV::outEdges(int fromVertex) const {
  return edges[fromVertex];
}

int GraphV::numVertices() const { return (int)edges.size(); }

int GraphV::addEdge(int from, int to) {
  edges[from].push_back({edgeId, to});
  return edgeId++;
}

} // namespace caide
