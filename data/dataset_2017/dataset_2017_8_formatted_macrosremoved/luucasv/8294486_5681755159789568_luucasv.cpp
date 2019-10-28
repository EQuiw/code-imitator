#include <bits/stdc++.h>

using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<ld, int> ii;

struct horse {
  ld e, s;
};

const int ms = 111;
const ld inf = 1e20;

int n;
horse h[ms];
long double calc[ms], dist[ms][ms];
int step;

long double dijkstra(int at, int ed) {
  priority_queue<ii, vector<ii>, greater<ii>> pq;
  pq.push(ii(0, at));
  for (int i = 0, __ = n; i < __; ++i)
    calc[i] = inf;
  calc[at] = 0;
  while (!pq.empty()) {
    ii tp = pq.top();
    pq.pop();
    if (tp.first > calc[tp.second])
      continue;
    if (tp.second == ed)
      break;
    for (int i = 0, __ = n; i < __; ++i) {
      if (i == tp.second || dist[tp.second][i] > h[tp.second].e)
        continue;
      ld ndist = tp.first + dist[tp.second][i] / h[tp.second].s;
      if (ndist < calc[i]) {
        pq.push(ii(ndist, i));
        calc[i] = ndist;
      }
    }
  }
  return calc[ed];
}

int main() {
  ios::sync_with_stdio(0);
  int t, cas = 1;
  cin >> t;
  while (t--) {
    cout << "Case #" << cas++ << ":";
    int q;
    cin >> n >> q;
    for (int i = 0, __ = n; i < __; ++i)
      cin >> h[i].e >> h[i].s;
    for (int i = 0, __ = n; i < __; ++i) {
      for (int j = 0, __ = n; j < __; ++j) {
        cin >> dist[i][j];
        if (dist[i][j] < 0)
          dist[i][j] = inf;
      }
      dist[i][i] = 0;
    }
    for (int k = 0, __ = n; k < __; ++k)
      for (int i = 0, __ = n; i < __; ++i)
        for (int j = 0, __ = n; j < __; ++j)
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    for (int i = 0, __ = q; i < __; ++i) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      cout << " " << setprecision(10) << fixed << dijkstra(u, v);
    }
    cout << endl;
  }
}
