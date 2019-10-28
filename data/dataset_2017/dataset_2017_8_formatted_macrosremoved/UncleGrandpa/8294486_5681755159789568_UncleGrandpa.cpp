/*input
2
3 1
2 3
2 4
4 4
-1 1 -1
-1 -1 1
-1 -1 -1
1 3
4 1
13 10
1 1000
10 8
5 5
-1 1 -1 -1
-1 -1 1 -1
-1 -1 -1 10
-1 -1 -1 -1
1 4
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
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
#include <utility>
#include <vector>
using namespace std;

const long long INF = 1e18;
long long n, q;
pair<long long, long long> a[105];
vector<vector<pair<long long, long long>>> e(105);
long long d2[105][105];
double dis[105];

void solve(long long l, long long r) {
  priority_queue<pair<double, long long>, vector<pair<double, long long>>,
                 greater<pair<double, long long>>>
      pq;
  fill(dis, dis + 105, 1e15);
  dis[l] = 0.0;
  pq.push(make_pair(0, l));
  while (!pq.empty()) {
    long long u = pq.top().second;
    pq.pop();
    for (long long i = 1; i <= n; i++) {
      if (i == u || d2[u][i] == INF)
        continue;
      if (d2[u][i] <= a[u].first &&
          dis[i] > dis[u] + (d2[u][i] * 1.0) / (a[u].second * 1.0)) {
        dis[i] = dis[u] + (d2[u][i] * 1.0) / (a[u].second * 1.0);
        pq.push(make_pair(dis[i], i));
      }
    }
  }
  cout << setprecision(10) << fixed << dis[r] << '\n';
}

void dijkstra(long long wh, long long sta) {
  priority_queue<pair<long long, long long>, vector<pair<long long, long long>>,
                 greater<pair<long long, long long>>>
      pq;
  for (long long i = 0; i <= n; i++)
    d2[wh][i] = INF;
  d2[wh][sta] = 0;
  pq.push(make_pair(0, sta));
  while (!pq.empty()) {
    long long u = pq.top().second;
    pq.pop();
    for (long long j = 0; j < e[u].size(); j++) {
      long long v = e[u][j].first;
      long long w = e[u][j].second;
      if (d2[wh][v] > d2[wh][u] + w) {
        d2[wh][v] = d2[wh][u] + w;
        pq.push(make_pair(d2[wh][v], v));
      }
    }
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  long long T;
  cin >> T;
  long long ct = 0;
  while (T--) {
    ct++;
    e.assign(105, vector<pair<long long, long long>>());
    cin >> n >> q;
    for (long long i = 1; i <= n; i++) {
      cin >> a[i].first >> a[i].second;
    }
    for (long long i = 1; i <= n; i++) {
      for (long long j = 1; j <= n; j++) {
        long long t;
        cin >> t;
        if (t != -1)
          e[i].push_back(make_pair(j, t));
      }
    }
    for (long long i = 1; i <= n; i++) {
      dijkstra(i, i);
    }
    while (q--) {
      long long u, v;
      cin >> u >> v;
      cout << "Case #" << ct << ": ";
      solve(u, v);
    }
  }
}
