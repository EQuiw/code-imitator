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

const int N = 1e6 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1},
          dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n, p;
double a[51];
void solve(int _id) {
  cin >> n >> p;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  set<pair<double, int>> can[n + 1];

  double mx = -inf;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= p; j++) {
      double x;
      cin >> x;
      mx = max(mx, x);
      can[i].insert({x, j});
    }

  mx += mx * 0.1;
  mx += 10;
  int ans = 0;
  for (int take = 1; take <= mx; take++) {
    vector<pair<double, int>> pos[n + 1];
    int mn = inf;
    for (int i = 1; i <= n; i++) {
      double l = (a[i] * take / 100.00) * 90.00,
             r = (a[i] * take / 100.00) * 110.000;
      auto it = can[i].lower_bound({l, -inf});
      for (int cnt = mn; cnt && it != can[i].end(); cnt--, it++) {
        if (it->first <= r)
          pos[i].push_back(*it);
        else
          break;
      }
      mn = min(mn, (int)pos[i].size());
    }
    ans += mn;
    if (mn) {
      for (int i = 1; i <= n; i++)
        for (int j = 0; j <= mn - 1; j++)
          can[i].erase(pos[i][j]);
    }
  }

  cout << "Case #" << _id << ": " << ans << '\n';
}

int main() {

  freopen("B-small-attempt0"
          ".in",
          "r", stdin);
  freopen("B-small-attempt0"
          ".out",
          "w", stdout);

  ios_base ::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++)
    solve(i);

  exit(0);
}
