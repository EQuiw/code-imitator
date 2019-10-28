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

#define Toktama "B-small-attempt2"

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

int n;
pair<int, int> a[7], b[7];
char c[] = {' ', 'R', 'O', 'Y', 'G', 'B', 'V'};
map<char, set<char>> bad;
bool check(char x, char y) {
  if (bad[x].count(y))
    return 0;
  return 1;
}
bool checkid(int x) {
  rep(i, 1, 6) if (a[i].s == x && a[i].f > 0) return 1;
  return 0;
}
void solve(int testcase) {
  cin >> n;
  rep(i, 1, 6) cin >> a[i].f, a[i].s = i;
  sort(a + 1, a + 1 + 6, greater<pair<int, int>>());
  rep(i, 1, 6) b[i] = a[i];
  int l = 1, r = 1;
  while (r + 1 <= n && a[r + 1].f == a[r].f)
    r++;
  cout << "Case #" << testcase << ": ";
  rep(i, 1, 6) {
    if (!a[i].f)
      break;
    string ans;
    ans += c[a[i].s];
    while (sz(ans) < n) {
      bool done = 0;
      rep(j, 1, 6) {
        if (a[j].f && check(ans.back(), c[a[j].s]))
          a[j].f--, ans += c[a[j].s], done = 1;
      }
      if (!done)
        break;
    }
    bool ok = 1;
    rep(j, 0, sz(ans) - 1) if (!check(ans[j], ans[(j + 1) % n])) {
      ok = 0;
      break;
    }
    if (ok && sz(ans) == n) {
      cout << ans << nl;
      return;
    }
    rep(j, 1, 6) a[j] = b[j];
  }
  cout << "IMPOSSIBLE\n";
}
int main() {
#ifdef Toktama
  freopen(Toktama ".in", "r", stdin);
  freopen(Toktama ".out", "w", stdout);
#endif
  Kazakhstan bad['R'].insert('R');
  bad['R'].insert('O');
  bad['R'].insert('V');

  bad['O'].insert('O');
  bad['O'].insert('V');
  bad['O'].insert('G');
  bad['O'].insert('R');
  bad['O'].insert('Y');

  bad['Y'].insert('Y');
  bad['Y'].insert('G');
  bad['Y'].insert('O');

  bad['G'].insert('G');
  bad['G'].insert('Y');
  bad['G'].insert('B');
  bad['G'].insert('O');
  bad['G'].insert('V');

  bad['B'].insert('B');
  bad['B'].insert('G');
  bad['B'].insert('V');

  bad['V'].insert('V');
  bad['V'].insert('R');
  bad['V'].insert('B');
  bad['V'].insert('G');
  bad['V'].insert('O');

  int T = 1;
  cin >> T;
  rep(i, 1, T) solve(i);
  ioi
}
