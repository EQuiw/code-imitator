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

#define _11day "B-small-attempt0"

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

const int N = 4686825 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1},
          dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n, t;
ll a[N];

void gen() {
  queue<ll> q;
  rep(i, 1, 9) q.push(i);
  while (sz(q)) {
    ll v = q.front();
    q.pop();

    if (v < (ll)1e18) {
      a[++n] = v;
      rep(i, v % 10, 9) q.push(v * 10 + i);
    }
  }
}

void solve(int id) {
  ll x;
  cin >> x;
  int pos = upper_bound(a + 1, a + 1 + n, x) - a - 1;
  cout << "Case #" << id << ": " << a[pos] << nl;
}
int main() {
#ifndef _11day
  freopen(_11day ".in", "r", stdin);
  freopen(_11day ".out", "w", stdout);
#endif

  Kazakhstan cin >> t;
  gen();
  rep(i, 1, t) solve(i);

  ioi
}
