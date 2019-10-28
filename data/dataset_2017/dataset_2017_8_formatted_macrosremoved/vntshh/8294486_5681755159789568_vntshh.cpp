#include <bits/stdc++.h>
using namespace std;

using namespace std;
typedef long double ldb;
typedef long long lld;
lld powm(lld base, lld exp, lld mod = 1000000007) {
  lld ans = 1;
  while (exp) {
    if (exp & 1)
      ans = (ans * base) % mod;
    exp >>= 1, base = (base * base) % mod;
  }
  return ans;
}
typedef vector<lld> vlld;
typedef pair<lld, lld> plld;
typedef map<lld, lld> mlld;
typedef set<lld> slld;

vector<plld> adj[105];
vector<pair<lld, ldb>> a[105];
lld second[105], e[105], mat[105][105], u, v;
void add(lld x) {
  queue<plld> q;
  for (auto i : adj[x])
    q.push(i);
  while (!q.empty()) {
    plld curr = q.front();
    q.pop();
    if (curr.second <= e[x]) {
      ldb tmp = ((ldb)curr.second / second[x]);
      a[x].push_back({curr.first, tmp});
      for (auto i : adj[curr.first])
        q.push({i.first, i.second + curr.second});
    }
  }
}
ldb dis[105];
bool vis[105] = {0};
class prioritize {
public:
  bool operator()(pair<lld, ldb> &p1, pair<lld, ldb> &p2) {
    return p1.second > p2.second;
  }
};
void dk(lld source) {
  priority_queue<pair<lld, ldb>, vector<pair<lld, ldb>>, prioritize> pq;
  pq.push(make_pair(source, dis[source] = 0));
  while (!pq.empty()) {
    pair<lld, ldb> curr = pq.top();
    pq.pop();
    if (vis[curr.first])
      continue;
    vis[curr.first] = true;
    for (lld i = 0; i < a[curr.first].size(); i++)
      if (!vis[a[curr.first][i].first] and
          a[curr.first][i].second + curr.second < dis[a[curr.first][i].first])
        pq.push(make_pair(a[curr.first][i].first,
                          (dis[a[curr.first][i].first] =
                               a[curr.first][i].second + curr.second)));
  }
}
int main() {

  freopen("19.in", "r", stdin);
  freopen("19.out", "w", stdout);
  lld t, n, q;
  cin >> t;
  for (lld tt = 1; tt < t + 1; tt++) {
    for (lld i = 0; i < 105; i++)
      adj[i].clear(), a[i].clear();
    cin >> n >> q;
    for (lld i = 1; i < n + 1; i++)
      cin >> e[i] >> second[i];
    for (lld i = 1; i < n + 1; i++)
      for (lld j = 1; j < n + 1; j++) {
        cin >> mat[i][j];
        if (mat[i][j] != -1)
          adj[i].push_back({j, mat[i][j]});
      }
    for (lld i = 1; i < n + 1; i++)
      add(i);
    cout << "Case #" << tt << ": ";
    while (q--) {
      cin >> u >> v;
      for (lld i = 1; i < n + 1; i++)
        vis[i] = 0, dis[i] = 1000111000111000111LL;
      dk(u);
      cout << fixed << setprecision(6) << dis[v] << " ";
    }
    cout << endl;
  }
  return 0;
}
