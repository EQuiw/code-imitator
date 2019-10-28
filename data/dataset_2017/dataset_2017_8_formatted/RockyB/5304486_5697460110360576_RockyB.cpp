#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define f first
#define s second

#define pb push_back
#define pp pop_back
#define mp make_pair

#define sz(x) (int)x.size()
#define sqr(x) ((x)*1ll * (x))
#define all(x) x.begin(), x.end()

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, l, r) for (int i = l; i >= r; i--)

#define dbg(x) cerr << (#x) << " --> " << (x) << nl;
#define Kazakhstan ios_base ::sync_with_stdio(0), cin.tie(0), cout.tie(0);

#define nl '\n'
#define ioi exit(0);

#define _3day "B-small-attempt0"

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

const int N = 1e6 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1},
          dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n, p;
double a[51];
void solve(int _id) {
  cin >> n >> p;
  rep(i, 1, n) cin >> a[i];
  set<pair<double, int>> can[n + 1];

  double mx = -inf;
  rep(i, 1, n) rep(j, 1, p) {
    double x;
    cin >> x;
    mx = max(mx, x);
    can[i].insert({x, j});
  }

  mx += mx * 0.1;
  mx += 10;
  int ans = 0;
  rep(take, 1, mx) {
    vector<pair<double, int>> pos[n + 1];
    int mn = inf;
    rep(i, 1, n) {
      double l = (a[i] * take / 100.00) * 90.00,
             r = (a[i] * take / 100.00) * 110.000;
      auto it = can[i].lower_bound({l, -inf});
      for (int cnt = mn; cnt && it != can[i].end(); cnt--, it++) {
        if (it->f <= r)
          pos[i].pb(*it);
        else
          break;
      }
      mn = min(mn, sz(pos[i]));
    }
    ans += mn;
    if (mn) {
      rep(i, 1, n) rep(j, 0, mn - 1) can[i].erase(pos[i][j]);
    }
  }

  cout << "Case #" << _id << ": " << ans << nl;
}

int main() {
#ifdef _3day
  freopen(_3day ".in", "r", stdin);
  freopen(_3day ".out", "w", stdout);
#endif

  Kazakhstan int T;
  cin >> T;
  rep(i, 1, T) solve(i);

  ioi
}
