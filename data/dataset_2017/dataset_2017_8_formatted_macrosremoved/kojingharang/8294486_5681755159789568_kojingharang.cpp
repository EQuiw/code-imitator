#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <vector>

#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

//#define PII pair<ll, ll>
template <typename T0, typename T1>
std::ostream &operator<<(std::ostream &os, const map<T0, T1> &v) {
  for (typename map<T0, T1>::const_iterator p = v.begin(); p != v.end(); p++) {
    os << p->first << ": " << p->second << " ";
  }
  return os;
}
template <typename T0, typename T1>
std::ostream &operator<<(std::ostream &os, const pair<T0, T1> &v) {
  os << v.first << ": " << v.second << " ";
  return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const vector<T> &v) {
  for (int i = 0; i < (int)v.size(); i++) {
    os << v[i] << " ";
  }
  return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const set<T> &v) {
  vector<T> tmp(v.begin(), v.end());
  os << tmp;
  return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const deque<T> &v) {
  vector<T> tmp(v.begin(), v.end());
  os << tmp;
  return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const vector<vector<T>> &v) {
  for (int i = 0; i < (int)v.size(); i++) {
    os << v[i] << endl;
  }
  return os;
}

struct Dijkstra {
  struct edge {
    int to;
    double cost;
  };
  vector<vector<edge>> G;
  vector<double> V;
  const double Max = 1LL << 60;
  Dijkstra(int N) {
    G = vector<vector<edge>>(N);
    V = vector<double>(N, Max);
  }
  void add_edge(int v0, int v1, double cost) {
    if (v0 < G.size() && v1 < G.size())
      G[v0].push_back((edge){v1, cost});
  }
  typedef pair<double, long long> PII;
  long long run(int S, int E) {
    V[S] = 0;
    priority_queue<PII> q;
    q.push(make_pair(0, S));
    while (q.size()) {
      PII el = q.top();
      q.pop();
      if (el.second == E)
        break;
      if (-el.first > V[el.second])
        continue;
      for (int i = 0; i < (int)G[el.second].size(); i++) {
        const edge &e = G[el.second][i];
        if (V[e.to] > V[el.second] + e.cost) {
          V[e.to] = V[el.second] + e.cost;
          q.push(make_pair(-V[e.to], e.to));
        }
      }
    }
    if (E < 0)
      return -1;
    return V[E] == Max ? -1 : V[E];
  }
};

/*

*/
int main() {
  int test_cases;
  cin >> test_cases;
  long long N, Q;
  string s;
  for (int ttt = 0, _n = (test_cases); (ttt) < (int)_n; ++ttt) {
    cin >> N >> Q;
    vector<long long> En(N), Sp(N);
    vector<vector<long long>> dist(N, vector<long long>(N)); // [i][j] i->j
    for (int i = 0, _n = (N); (i) < (int)_n; ++i)
      cin >> En[i] >> Sp[i];
    for (int i = 0, _n = (N); (i) < (int)_n; ++i)
      for (int j = 0, _n = (N); (j) < (int)_n; ++j)
        cin >> dist[i][j];
    long long dummy;
    cin >> dummy >> dummy;

    // node: (cityIdx, speedIdx)
    Dijkstra d(N * N);
    for (int i = 0, _n = (N); (i) < (int)_n; ++i) {
      long long L = 0;
      for (int j = (int)i + 1, _b = (int)(N); (j) < _b; ++j) {
        L += dist[j - 1][j];
        if (dist[j - 1][j] == -1 || L > En[i])
          break;

        double t = (double)L / Sp[i];
        //				DD(i);DD(j);DD(t);
        // のりかえる
        d.add_edge(i * N + i, j * N + j, t);
        // のりかえない
        d.add_edge(i * N + i, j * N + i, t);
      }
    }
    d.run(0 * N + 0, -1);
    double ans = 1e100;
    //		DD(d.V);
    for (int i = 0, _n = (N); (i) < (int)_n; ++i)
      ans = min(ans, d.V[(N - 1) * N + i]);

    printf("Case #%d: %.9f\n", ttt + 1, ans);
    //		return 0;
  }
  return 0;
}
