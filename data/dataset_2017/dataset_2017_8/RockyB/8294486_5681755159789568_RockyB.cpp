#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

#define f first
#define s second

#define pb push_back
#define pp pop_back
#define mp make_pair

#define sz(x) (int)x.size()
#define sqr(x) ((ld)(x) * (x))
#define all(x) x.begin(), x.end()

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, l, r) for (int i = l; i >= r; i--)

#define dbg(x) cerr << (#x) << " --> " << (x) << nl;
#define Kazakhstan ios_base :: sync_with_stdio(0), cin.tie(0), cout.tie(0);

#define nl '\n'
#define ioi exit(0);

#define Toktama "C-small-attempt0"

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef tree < pair <int, int>, null_type, less < pair <int, int> >, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int N = 100 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1}, dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n, q;
ll e[N], s[N], a[N][N];
bool was[N];
ld d[N];
ll dist[N];
vector < pair <int, int> > go[N];
vector < pair <int, ld> > g[N];
void bfs(int x) {
  rep(i, 1, n)
    dist[i] = linf;
  dist[x] = 0;
  set < pair <ll, int> > st;
  st.insert({0, x});
  while (sz(st)) {
    pair <ll, int> v = *st.begin();
    st.erase(st.begin());
    for (auto to : go[v.s])
      if (v.f + to.s < dist[to.f]) {
        st.insert({dist[to.f], to.f});
        dist[to.f] = v.f + to.s;
        st.insert({dist[to.f], to.f});
      }
  }
  rep(i, 1, n)
    if (dist[i] != -1 && e[x] >= dist[i]) g[x].pb({i, (ld)dist[i] / (ld)s[x]});
}
ld get(int v, int u) {
  rep(i, 1, n)
    d[i] = linf;
  d[v] = 0;
  set < pair <ld, int> > st;
  st.insert({0, v});
  while (sz(st)) {
    pair <ld, int> x = *st.begin();
    st.erase(st.begin());
    for (auto to : g[x.s])
      if (x.f + to.s < d[to.f]) {
        st.erase({d[to.f], to.f});
        d[to.f] = x.f + to.s;
        st.insert({d[to.f], to.f});
      }
  }
  return d[u];
}
void solve(int id) {
  cin >> n >> q;
  rep(i, 1, n)
    cin >> e[i] >> s[i];
  rep(i, 1, n)
    rep(j, 1, n) {
      cin >> a[i][j];
      if (a[i][j] != -1) go[i].pb({j, a[i][j]});
    }
  rep(i, 1, n)
    bfs(i);
  cout << "Case #" << id << ": ";
  rep(i, 1, q) {
    int v, u;
    cin >> v >> u;
    cout << setprecision(10) << fixed << get(v, u) << ' ';
  }
  cout << nl;
  rep(i, 1, n)
    go[i].clear(), g[i].clear();
}

int main() {
  #ifdef Toktama
    freopen (Toktama".in", "r", stdin);
    freopen (Toktama".out", "w", stdout);
  #endif
  Kazakhstan
  int T = 1;
  cin >> T;
  rep(i, 1, T)
    solve(i);
  ioi
}
