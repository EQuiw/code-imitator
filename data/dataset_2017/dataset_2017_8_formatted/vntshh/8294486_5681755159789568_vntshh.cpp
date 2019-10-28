#include <bits/stdc++.h>
#define rep(i, start, lim) for (lld i = start; i < lim; i++)
#define repd(i, start, lim) for (lld i = start; i >= lim; i--)
#define scan(x) scanf("%lld", &x)
#define print(x) printf("%lld ", x)
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define br printf("\n")
#define YES printf("YES\n")
#define NO printf("NO\n")
#define all(c) (c).begin(), (c).end()
using namespace std;
#define INF 1011111111
#define LLINF 1000111000111000111LL
#define EPS (double)1e-10
#define MOD 1000000007
#define PI 3.14159265358979323
using namespace std;
typedef long double ldb;
typedef long long lld;
lld powm(lld base, lld exp, lld mod = MOD) {
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
#define N 105
vector<plld> adj[N];
vector<pair<lld, ldb>> a[N];
lld s[N], e[N], mat[N][N], u, v;
void add(lld x) {
  queue<plld> q;
  for (auto i : adj[x])
    q.push(i);
  while (!q.empty()) {
    plld curr = q.front();
    q.pop();
    if (curr.s <= e[x]) {
      ldb tmp = ((ldb)curr.s / s[x]);
      a[x].pb({curr.f, tmp});
      for (auto i : adj[curr.f])
        q.push({i.f, i.s + curr.s});
    }
  }
}
ldb dis[N];
bool vis[N] = {0};
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
    rep(i, 0, a[curr.first].size()) if (!vis[a[curr.first][i].first] and
                                        a[curr.first][i].second + curr.second <
                                            dis[a[curr.first][i].first])
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
  rep(tt, 1, t + 1) {
    rep(i, 0, N) adj[i].clear(), a[i].clear();
    cin >> n >> q;
    rep(i, 1, n + 1) cin >> e[i] >> s[i];
    rep(i, 1, n + 1) rep(j, 1, n + 1) {
      cin >> mat[i][j];
      if (mat[i][j] != -1)
        adj[i].pb({j, mat[i][j]});
    }
    rep(i, 1, n + 1) add(i);
    cout << "Case #" << tt << ": ";
    while (q--) {
      cin >> u >> v;
      rep(i, 1, n + 1) vis[i] = 0, dis[i] = LLINF;
      dk(u);
      cout << fixed << setprecision(6) << dis[v] << " ";
    }
    cout << endl;
  }
  return 0;
}