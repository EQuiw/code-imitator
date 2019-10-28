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
#define sqr(x) ((ld)(x) * (x))
#define all(x) x.begin(), x.end()

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, l, r) for (int i = l; i >= r; i--)

#define dbg(x) cerr << (#x) << " --> " << (x) << nl;
#define Kazakhstan ios_base ::sync_with_stdio(0), cin.tie(0), cout.tie(0);

#define nl '\n'
#define ioi exit(0);

#define Toktama "A-small-attempt0"

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

int n;
double d;
double k[N], s[N];
void solve(int id) {
  cin >> d >> n;
  rep(i, 1, n) cin >> k[i] >> s[i];
  double res = -linf;
  rep(i, 1, n) res = max(res, (d - k[i]) / s[i]);
  cout << "Case #" << id << ": " << setprecision(10) << fixed << d / res << nl;
}
int main() {
#ifdef Toktama
  freopen(Toktama ".in", "r", stdin);
  freopen(Toktama ".out", "w", stdout);
#endif
  Kazakhstan int T = 1;
  cin >> T;
  rep(i, 1, T) solve(i);
  ioi
}
