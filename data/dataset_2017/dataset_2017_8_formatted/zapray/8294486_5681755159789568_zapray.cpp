#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
typedef double ll;
#define MODD(a, b) (((a) % (b) + (b)) % (b))
#define EPS 1E-5
#define REP(i, s, t) for (int i = (s); i < (t); i++)
#define FILL(x, v) memset(x, v, sizeof(x))

using namespace std;

vector<vector<int>> edge;

struct horse {
  int e, s;
  horse(int ee, int ss) : e(ee), s(ss) {}
};

vector<horse> horses;

//
vector<pair<double, int>> D; // time, energe left on that horse

int N, Q;

void dijkstra(int s) {
  D.clear();
  D = vector<pair<double, int>>(N * N, pair<double, int>(9E99, 0));

  set<pair<pair<double, int>, int>> pq; //  ((time, eng), x)

  int x = s * N + s;
  D[x] = make_pair(0, horses[s].e);

  pq.insert(make_pair(D[x], x));

  while (!pq.empty()) {
    x = pq.begin()->second;
    pq.erase(pq.begin());

    int energyleft = D[x].second;
    int xcity = x / N;
    int curh = x % N;

    int y;
    for (int ycity = 0; ycity < N; ycity++) {
      if (edge[xcity][ycity] == -1)
        continue;

      // dont change horse
      y = ycity * N + curh;
      if (energyleft >= edge[xcity][ycity]) {
        pair<double, int> newD(D[x].first +
                                   double(edge[xcity][ycity]) / horses[curh].s,
                               energyleft - edge[xcity][ycity]);
        if (newD < D[y]) {
          pq.erase(make_pair(D[y], y));
          D[y] = newD;
          pq.insert(make_pair(D[y], y));
        }
      }

      // use horse x
      curh = xcity;
      y = ycity * N + curh;
      energyleft = horses[curh].e;
      if (energyleft >= edge[xcity][ycity]) {
        pair<double, int> newD(D[x].first +
                                   double(edge[xcity][ycity]) / horses[curh].s,
                               energyleft - edge[xcity][ycity]);
        if (newD < D[y]) {
          pq.erase(make_pair(D[y], y));
          D[y] = newD;
          pq.insert(make_pair(D[y], y));
        }
      }

    } // ycity
  }
}

int main() {
  int T;
  cin >> T;
  for (int cs = 1; cs <= T; cs++) {
    printf("Case #%d: ", cs);

    cin >> N >> Q;
    horses.clear();
    for (int i = 0; i < N; i++) {
      int e, s;
      cin >> e >> s;
      horses.emplace_back(e, s);
    }

    //
    horses.emplace_back(0, 0); // last fake horse

    edge.clear();
    edge.resize(N);
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) {
        int d;
        cin >> d;
        edge[i].push_back(d);
      }

    for (int i = 0; i < Q; i++) {
      int u, v;
      cin >> u >> v;
      u--;
      v--;
      dijkstra(u);
      pair<double, int> best(9E99, 0);
      for (int h = 0; h < N; h++) {
        best = min(best, D[v * N + h]);
      }
      printf("%.6lf ", best.first);
    }
    puts("");
  }
  return 0;
}