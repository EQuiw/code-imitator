#include <bits/stdc++.h>
#define fr(a, b, c) for (int a = b, __ = c; a < __; ++a)
#define dbg(x) cerr << ">>>> " << x << endl;
#define _ << " , " <<
#define Y second
#define X first

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
  fr(i, 0, n) calc[i] = inf;
  calc[at] = 0;
  while (!pq.empty()) {
    ii tp = pq.top();
    pq.pop();
    if (tp.X > calc[tp.Y])
      continue;
    if (tp.Y == ed)
      break;
    fr(i, 0, n) {
      if (i == tp.Y || dist[tp.Y][i] > h[tp.Y].e)
        continue;
      ld ndist = tp.X + dist[tp.Y][i] / h[tp.Y].s;
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
    fr(i, 0, n) cin >> h[i].e >> h[i].s;
    fr(i, 0, n) {
      fr(j, 0, n) {
        cin >> dist[i][j];
        if (dist[i][j] < 0)
          dist[i][j] = inf;
      }
      dist[i][i] = 0;
    }
    fr(k, 0, n) fr(i, 0, n) fr(j, 0, n) dist[i][j] =
        min(dist[i][j], dist[i][k] + dist[k][j]);

    fr(i, 0, q) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      cout << " " << setprecision(10) << fixed << dijkstra(u, v);
    }
    cout << endl;
  }
}