/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL

//#   define FAST

#include <bits/stdc++.h>

using namespace std;

/* aliases */
using vi = vector<int>;
using pi = pair<int, int>;
using ll = long long int;

/* shortcut macros */
/* trace macro */
/* util functions */
template <typename T1, typename T2, typename T3>
T1 modpow(T1 _a, T2 p, T3 mod) {
  assert(p >= 0);
  ll ret = 1, a = _a;

  if (a < 0) {
    a %= mod;
    a += mod;
  }

  if (a >= mod) {
    a %= mod;
  }

  for (; p > 0; p /= 2) {
    if (p & 1)
      ret = ret * a % mod;
    a = a * a % mod;
  }

  return ret;
}

/* constants */
constexpr int dx[] = {-1, 0, 1, 0, 1, 1, -1, -1};
constexpr int dy[] = {0, -1, 0, 1, 1, -1, 1, -1};
constexpr auto PI = 3.14159265358979323846L;
constexpr auto oo = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 3, mx_p = 8;
int n, p;
int req[mx_n];
int avail[mx_n][mx_p];

class Range {
public:
  int lo, hi;
  Range() {
    lo = -oo;
    hi = oo;
  }

  Range(int l, int h) {
    lo = l;
    hi = h;
  }

  bool isvalid() const { return lo > 0 && lo <= hi; }

  Range intersect(const Range &r) const {
    return Range(max(lo, r.lo), min(hi, r.hi));
  }
} ranges[mx_n][mx_p];

Range calc(int i, int j) {
  int r = req[i], a = avail[i][j];
  Range ret(0, 0);

  ret = Range((10 * a + 11 * r - 1) / (11 * r), 10 * a / (9 * r));

  // trace(i, j, r, a, ret.lo, ret.hi);
  return ret;
}

void init() {
  for (int i = ((0)), _i = ((n)-1); i <= _i; ++i)
    for (int j = ((0)), _j = ((p)-1); j <= _j; ++j)
      ranges[i][j] = calc(i, j);
}

int dp[(1 << 16)];
int solve() {
  init();

  for (int mask = (1 << (n * p)) - 1; mask >= 0; --mask) {
    dp[mask] = 0;
    for (int nxt1 = ((0)), _nxt1 = ((n * p) - 1); nxt1 <= _nxt1; ++nxt1)
      if (!(((mask) >> nxt1) & 1)) {
        Range r = ranges[nxt1 / p][nxt1 % p];
        if (n == 1) {
          if (r.isvalid())
            dp[mask] = max(dp[mask], 1 + dp[mask | (1 << nxt1)]);
        } else {
          for (int nxt2 = ((0)), _nxt2 = ((n * p) - 1); nxt2 <= _nxt2; ++nxt2)
            if (nxt2 / p != nxt1 / p && !(((mask) >> nxt2) & 1)) {
              Range cur = r.intersect(ranges[nxt2 / p][nxt2 % p]);
              if (cur.isvalid())
                dp[mask] =
                    max(dp[mask], 1 + dp[mask | (1 << nxt1) | (1 << nxt2)]);
            }
        }
      }
    // trace(mask, dp[mask]);
  }

  return dp[0];
}

int main() {
  int t;
  cin >> t;
  for (int kase = (1), _kase = (t); kase <= _kase; ++kase) {
    cin >> n >> p;
    for (int i = ((0)), _i = ((n)-1); i <= _i; ++i)
      cin >> req[i];
    for (int i = ((0)), _i = ((n)-1); i <= _i; ++i)
      for (int j = ((0)), _j = ((p)-1); j <= _j; ++j)
        cin >> avail[i][j];

    int ans = solve();
    cout << "Case #" << kase << ": " << ans << '\n';
  }

  return 0;
}
