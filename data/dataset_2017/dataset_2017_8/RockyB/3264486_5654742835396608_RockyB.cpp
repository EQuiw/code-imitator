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

#define _11day "C-small-1-attempt4"

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef tree < pair <int, int>, null_type, less < pair <int, int> >, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int N = 1e6 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1}, dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n, k;
bool bad[N];

pair <int, int> calc(int p) {
  pair <int, int> res = {0, 0};
  rep(i, p, n) {
    if (bad[i]) {
      break;
    }
    res.s++;
  }
  per(i, p, 1) {
    if (bad[i]) {
      break;
    }
    res.f++;
  }
  return res;
}

pair <int, int> get(pair <int, int> l, pair <int, int> r) {
  if (min(l.f, l.s) > min(r.f, r.s)) return l;
  if (min(l.f, l.s) < min(r.f, r.s)) return r;
  if (max(l.f, l.s) > max(r.f, r.s)) return l;
  return r;
}

void solve(int id) {
  scanf ("%d%d", &n, &k);
  memset(bad, 0, sizeof(bad));
  rep(i, 1, k) {
    pair <int, int> mx = {-1, -1};
    int idx = -1;
    rep(j, 1, n) {
      pair <int, int> cur = calc(j);
      pair <int, int> res = get(mx, cur);
      if (mx != res) idx = j, mx = res;
    }
    if (i == k) {
      cout << "Case #" << id << ": " << max(mx.f, mx.s) - 1 << ' ' << min(mx.f, mx.s) - 1 << nl;
      return;
    }
    bad[idx] = 1;
  }
}

int T;
int main() {
  #ifdef _11day
    freopen (_11day".in", "r", stdin);
    freopen (_11day".out", "w", stdout);
  #endif

  scanf ("%d", &T);
  rep(i, 1, T)
    solve(i);
  ioi
}

