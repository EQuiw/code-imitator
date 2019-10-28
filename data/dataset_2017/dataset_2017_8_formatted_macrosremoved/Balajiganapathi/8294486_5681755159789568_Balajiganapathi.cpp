/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL

//#   define FAST

#include <bits/stdc++.h>

using namespace std;

/* aliases */
using vi = vector<int>;
using pi = pair<int, int>;
using ll = long long int;
using ld = long double;

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
constexpr auto oo = numeric_limits<ll>::max() / 2 - 2;
constexpr auto eps = 1e-7;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 102;

ld mtime[mx_n][mx_n];
int n, e[mx_n], s[mx_n], d[mx_n][mx_n];

ld dp[mx_n][mx_n];

ld rec(int i, int h) {
  if (i == n - 1)
    return 0;
  ld &ret = dp[i][h];
  if (ret > -eps)
    return ret;
  ret = oo;

  // next switch
  int sofar = 0;
  for (int j = ((i + 1)), _j = ((n)-1); j <= _j; ++j) {
    sofar += d[j - 1][j];
    if (sofar > e[h])
      break;
    ret = min(ret, rec(j, j) + 1.0 * sofar / s[h]);
  }

  return ret;
}

ld solve(int u, int v) {
  for (int i = ((0)), _i = ((mx_n)-1); i <= _i; ++i)
    for (int j = ((0)), _j = ((mx_n)-1); j <= _j; ++j)
      dp[i][j] = -oo;
  return rec(u, u);
}

int main() {
  int _t;
  cin >> _t;
  for (int kase = (1), _kase = (_t); kase <= _kase; ++kase) {
    int q;
    cin >> n >> q;
    for (int i = ((0)), _i = ((n)-1); i <= _i; ++i)
      cin >> e[i] >> s[i];
    for (int i = ((0)), _i = ((n)-1); i <= _i; ++i)
      for (int j = ((0)), _j = ((n)-1); j <= _j; ++j)
        cin >> d[i][j];
    cout << "Case #" << kase << ":";
    while (q--) {
      int u, v;
      cin >> u >> v;
      --u;
      --v;
      cout.precision(10);
      cout << " " << fixed << solve(u, v);
    }
    cout << endl;
  }

  return 0;
}
