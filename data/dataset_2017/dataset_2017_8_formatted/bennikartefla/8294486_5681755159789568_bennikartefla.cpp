#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define iter(it, c)                                                            \
  for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const long double INF = 1000000000000;
const long double pi = acos(-1);
typedef pair<long double, int> di;

int mxdist[120];
int conspeed[120];
long double matrix[120][120];
long double matrix2[120][120];

void fill(int at) {
  bool vis[120];
  memset(vis, 0, sizeof(vis));
  vis[at] = true;
  priority_queue<pair<long double, int>, vector<di>, greater<di>> q;
  q.push(pair<long double, int>(0, at));
  while (!q.empty()) {
    int cur = q.top().second;
    long double range = q.top().first;
    q.pop();
    rep(i, 0, 120) {
      if (matrix[cur][i] != -1 && i != cur && !vis[i]) {
        long double thedist = matrix[cur][i];
        range += thedist;
        if (range > mxdist[at]) {
          range -= thedist;
          continue;
        }
        matrix2[at][i] = min(range / conspeed[at], matrix2[at][i]);
        q.push(pair<long double, int>(range, i));
        range -= thedist;
      }
    }
  }
}

long double query(int start, int end) {
  priority_queue<di, vector<di>, greater<di>> pq;
  pq.push(di(0, start));
  long double dist[150];
  bool vis[150];
  rep(i, 0, 150) dist[i] = INF;
  memset(vis, 0, sizeof(vis));
  dist[start] = 0;
  while (!pq.empty()) {
    di cur = pq.top();
    pq.pop();
    rep(i, 0, 120) {
      if (matrix2[cur.second][i] != -1) {
        long double ne = min(dist[i], cur.first + matrix2[cur.second][i]);
        if (ne >= dist[i])
          continue;
        dist[i] = ne;
        pq.push(di(dist[i], i));
      }
    }
  }
  return dist[end];
}

int main() {
  cin.sync_with_stdio(false);
  ofstream fout("ansc.txt");
  int t;
  cin >> t;
  rep(u, 0, t) {
    int n, q;
    memset(mxdist, 0, sizeof(mxdist));
    memset(conspeed, 0, sizeof(conspeed));
    rep(i, 0, 120) rep(a, 0, 120) matrix[i][a] = -1;
    rep(i, 0, 120) rep(a, 0, 120) matrix2[i][a] = INF;
    cin >> n >> q;
    rep(i, 0, n) {
      int dist, speed;
      cin >> dist >> speed;
      mxdist[i] = dist;
      conspeed[i] = speed;
    }
    rep(i, 0, n) rep(a, 0, n) cin >> matrix[i][a];
    rep(i, 0, n) fill(i);
    rep(i, 0, 120) rep(a, 0, 120) if (matrix2[i][a] == INF) matrix2[i][a] = -1;
    vector<ii> all(q);
    rep(i, 0, q) cin >> all[i].first >> all[i].second;
    fout << "Case #" << u + 1 << ": ";
    rep(i, 0, q) {
      fout << setprecision(9) << fixed
           << query(all[i].first - 1, all[i].second - 1) << " ";
    }
    fout << endl;
  }
  return 0;
}
