#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

const int N = 100 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1},
          dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n, q;
ll e[N], second[N], a[N][N];
bool was[N];
ld d[N];
ll dist[N];
vector<pair<int, int>> go[N];
vector<pair<int, ld>> g[N];
void bfs(int x) {
  for (int i = 1; i <= n; i++)
    dist[i] = linf;
  dist[x] = 0;
  set<pair<ll, int>> st;
  st.insert({0, x});
  while ((int)st.size()) {
    pair<ll, int> v = *st.begin();
    st.erase(st.begin());
    for (auto to : go[v.second])
      if (v.first + to.second < dist[to.first]) {
        st.insert({dist[to.first], to.first});
        dist[to.first] = v.first + to.second;
        st.insert({dist[to.first], to.first});
      }
  }
  for (int i = 1; i <= n; i++)
    if (dist[i] != -1 && e[x] >= dist[i])
      g[x].push_back({i, (ld)dist[i] / (ld)second[x]});
}
ld get(int v, int u) {
  for (int i = 1; i <= n; i++)
    d[i] = linf;
  d[v] = 0;
  set<pair<ld, int>> st;
  st.insert({0, v});
  while ((int)st.size()) {
    pair<ld, int> x = *st.begin();
    st.erase(st.begin());
    for (auto to : g[x.second])
      if (x.first + to.second < d[to.first]) {
        st.erase({d[to.first], to.first});
        d[to.first] = x.first + to.second;
        st.insert({d[to.first], to.first});
      }
  }
  return d[u];
}
void solve(int id) {
  cin >> n >> q;
  for (int i = 1; i <= n; i++)
    cin >> e[i] >> second[i];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
      if (a[i][j] != -1)
        go[i].push_back({j, a[i][j]});
    }
  for (int i = 1; i <= n; i++)
    bfs(i);
  cout << "Case #" << id << ": ";
  for (int i = 1; i <= q; i++) {
    int v, u;
    cin >> v >> u;
    cout << setprecision(10) << fixed << get(v, u) << ' ';
  }
  cout << '\n';
  for (int i = 1; i <= n; i++)
    go[i].clear(), g[i].clear();
}

int main() {

  freopen("C-small-attempt0"
          ".in",
          "r", stdin);
  freopen("C-small-attempt0"
          ".out",
          "w", stdout);

  ios_base ::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  for (int i = 1; i <= T; i++)
    solve(i);
  exit(0);
}
