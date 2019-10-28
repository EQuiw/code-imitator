

#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

//#include <cstdint>
//#include <cstdlib>
#include <cassert>
//#include <cctype>
#include <algorithm>
#include <climits>
#include <cmath>
#include <ctime>
#include <functional>
#include <numeric>

#include <array>
#include <bitset>
#include <cstring>
#include <deque>
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
typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld PI = acosl(ld(-1));
const ld EPS = 1e-9;

template <typename T> inline T sqr(const T &first) { return first * first; }

template <typename T> inline T abs(const T &first) {
  return first > 0 ? first : -first;
}

inline bool inside(int first, int second, int n, int m) {
  return first >= 1 && first <= n && second >= 1 && second <= m;
}

inline int rnd() { return abs(rand() ^ (rand() << 15)); }

inline int rnd(int n) {
  assert(n > 0);
  return rnd() % n;
}

inline int rnd(int lf, int rg) { return lf + rnd(rg - lf + 1); }

inline li rndLL() { return rnd() * 1LL * rnd() + rnd(); }

const int dx[4] = {-1, 0, +1, 0};
const int dy[4] = {0, +1, 0, -1};

const int dx8[8] = {-1, -1, 0, +1, +1, +1, 0, -1};
const int dy8[8] = {0, +1, +1, +1, 0, -1, -1, -1};

const int N = int(111);

int n, q;
int g[N][N];
pt qs[N];
int maxdist[N], speed[N];

inline void gen() { return; }

inline bool read() {
  if (scanf("%d %d", &n, &q) != 2)
    return false;
  for (int i = 0; i < int(n); i++)
    assert(scanf("%d %d", &maxdist[i], &speed[i]) == 2);
  for (int i = 0; i < int(n); i++)
    for (int j = 0; j < int(n); j++)
      assert(scanf("%d", &g[i][j]) == 1);
  for (int i = 0; i < int(q); i++) {
    assert(scanf("%d %d", &qs[i].first, &qs[i].second) == 2);
    qs[i].first--;
    qs[i].second--;
  }
  return true;
}

li d[N][N];
ld minTime[N][N];

inline void Dijkstra(li *d, int s) {
  for (int i = 0; i < int(N); i++)
    d[i] = INF64;
  d[s] = 0;
  set<pair<li, int>> Q;
  Q.insert(make_pair(0, s));

  while (!Q.empty()) {
    int v = Q.begin()->second;
    Q.erase(Q.begin());
    for (int i = 0; i < int(n); i++) {
      int to = i;
      if (g[v][to] != -1 && d[v] + g[v][to] < d[to]) {
        Q.erase(make_pair(d[to], to));
        d[to] = d[v] + g[v][to];
        Q.insert(make_pair(d[to], to));
      }
    }
  }
}

inline void prepareTimes() {
  for (int i = 0; i < int(n); i++)
    Dijkstra(d[i], i);
  for (int i = 0; i < int(N); i++)
    for (int j = 0; j < int(N); j++)
      minTime[i][j] = INF64;
  for (int i = 0; i < int(n); i++)
    for (int j = 0; j < int(n); j++)
      if (d[i][j] < INF64 / 2 && d[i][j] <= maxdist[i]) {
        minTime[i][j] = ld(d[i][j]) / speed[i];
      }
}

ld dp[N][N];
bool was[N];

inline void solve() {
  for (int i = 0; i < int(N); i++)
    was[i] = false;
  for (int kk = 0; kk < int(q); kk++) {
    int s = qs[kk].first, t = qs[kk].second;
    for (int i = 0; i < int(N); i++)
      for (int j = 0; j < int(N); j++)
        dp[i][j] = INF64;
    dp[0][s] = 0;
    for (int step = 0; step < int(N - 1); step++)
      for (int v = 0; v < int(n); v++) {
        ld cur = dp[step][v];
        if (cur > INF64 / 2)
          continue;
        for (int to = 0; to < int(n); to++)
          if (minTime[v][to] < INF64 / 2) {
            dp[step + 1][to] = min(dp[step + 1][to], cur + minTime[v][to]);
          }
      }

    ld nans = INF64;
    for (int step = 0; step < int(N); step++)
      nans = min(nans, dp[step][t]);
    assert(nans < INF64 / 2);
    if (kk)
      cout << ' ';
    cout << nans;
  }
  cout << endl;
  return;
}

int main() {
  // assert(false);

  cout << setprecision(10) << fixed;
  cerr << setprecision(10) << fixed;

  srand(int(time(NULL)));

  int T = 1;

  assert(scanf("%d", &T) == 1);

  for (int i = 0; i < int(T); i++) {

    assert(read());
    // read();
    prepareTimes();
    cout << "Case #" << i + 1 << ": ";
    solve();
    cerr << "curTime == " << clock() << " ms" << endl;
  }

  return 0;
}
