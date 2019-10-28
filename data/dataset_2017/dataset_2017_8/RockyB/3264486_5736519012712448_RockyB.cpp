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
#define sqr(x) ((x) * 1ll * (x))
#define all(x) x.begin(), x.end()

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, l, r) for (int i = l; i >= r; i--)

#define dbg(x) cerr << (#x) << " --> " << (x) << nl;
#define Kazakhstan ios_base :: sync_with_stdio(0), cin.tie(0), cout.tie(0);

#define nl '\n'
#define ioi exit(0);

#define _11day ""

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef tree < pair <int, int>, null_type, less < pair <int, int> >, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int N = 4e5 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1}, dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n, k, t;
int d[1 << 14];
string s;

int get_mask(string x) {
  int res = 0;
  reverse(all(x));
  rep(i, 0, sz(x) - 1)
    if (x[i] == '+') res |= 1 << i;
  return res;
}
int inverse(int l, int x) {
  rep(i, l, l + k - 1)
    x ^= 1 << i;
  return x;
}

void solve(int id) {
  cin >> s >> k;
  n = sz(s);

  memset(d, -1, sizeof(d));
  queue <int> q;
  int st = get_mask(s);
  d[st] = 0;
  q.push(st);

  while (sz(q)) {
    int v = q.front();
    q.pop();
    rep(i, 0, n - 1 - k + 1) {
      int x = inverse(i, v);
      if (d[x] == -1) d[x] = d[v] + 1, q.push(x);
    }
  }

  int res = d[(1 << n) - 1];
  cout << "Case #" << id << ": ";
  if (res == -1) cout << "IMPOSSIBLE" << nl;
  else cout << res << nl;
}
int main() {
  #ifndef _11day
    freopen (_11day".in", "r", stdin);
    freopen (_11day".out", "w", stdout);
  #endif

//  freopen ("A-small-attempt0.in", "r", stdin);
  cin >> t;
  rep(i, 1, t)
    solve(i);
  ioi
}
