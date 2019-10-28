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
constexpr int mx_r = 25;
string cake[mx_r];
string ans[mx_r];
int r, c;

int dp[(1 << 25)];
int prv[(1 << 25)];
int prvi[(1 << 25)];
int can[mx_r][mx_r][mx_r][mx_r];
int pmask[mx_r][mx_r][mx_r][mx_r];

void init() {
  for (int i1 = ((0)), _i1 = ((r)-1); i1 <= _i1; ++i1)
    for (int j1 = ((0)), _j1 = ((c)-1); j1 <= _j1; ++j1)
      for (int i2 = ((i1)), _i2 = ((r)-1); i2 <= _i2; ++i2)
        for (int j2 = ((j1)), _j2 = ((c)-1); j2 <= _j2; ++j2) {
          can[i1][j1][i2][j2] = -1;
          pmask[i1][j1][i2][j2] = 0;
          for (int i = (i1), _i = (i2); i <= _i; ++i)
            for (int j = (j1), _j = (j2); j <= _j; ++j) {
              if (cake[i][j] != '?') {
                if (can[i1][j1][i2][j2] == -1)
                  can[i1][j1][i2][j2] = cake[i][j];
                else
                  can[i1][j1][i2][j2] = -1;
              }
              pmask[i1][j1][i2][j2] |= (1 << (i * c + j));
            };
        }
}

int solve(int mask) {
  int &ret = dp[mask];
  if (ret != -1)
    return ret;
  if (mask == (1 << (r * c)) - 1)
    return ret = 1;

  ret = 0;
  for (int i1 = ((0)), _i1 = ((r)-1); i1 <= _i1; ++i1)
    for (int j1 = ((0)), _j1 = ((c)-1); j1 <= _j1; ++j1) {
      if (ret)
        break;
      for (int i2 = ((i1)), _i2 = ((r)-1); i2 <= _i2; ++i2)
        for (int j2 = ((j1)), _j2 = ((c)-1); j2 <= _j2; ++j2) {
          if (ret)
            break;
          if ((mask & pmask[i1][j1][i2][j2]) == 0 &&
              can[i1][j1][i2][j2] != -1) {
            int nmask = mask | pmask[i1][j1][i2][j2];
            if (solve(nmask)) {
              prv[nmask] = mask;
              prvi[nmask] = can[i1][j1][i2][j2];
              ;
              ret = 1;
              break;
            }
          }
        }
    }

    ;
  return ret;
}

void getAns() {
  int cur = (1 << (r * c)) - 1;
  for (int i = ((0)), _i = ((r)-1); i <= _i; ++i)
    ans[i] = string(c, '?');
  while (cur > 0) {
    int nxt = (cur ^ prv[cur]);
    ;
    assert(prvi[cur]);
    for (int k = ((0)), _k = ((r * c) - 1); k <= _k; ++k)
      if ((((nxt) >> k) & 1)) {
        ans[k / c][k % c] = prvi[cur];
      }
    cur ^= nxt;
  }
}

int main() {
  memset(can, -1, sizeof(can));
  int t;
  cin >> t;
  for (int kase = (1), _kase = (t); kase <= _kase; ++kase) {
    cin >> r >> c;
    for (int i = ((0)), _i = ((r)-1); i <= _i; ++i)
      cin >> cake[i];
    // fo(i, r) trace(i, cake[i]);
    memset(dp, -1, sizeof(dp));
    init();
    assert(solve(0));
    getAns();

    cout << "Case #" << kase << ":\n";
    for (int i = ((0)), _i = ((r)-1); i <= _i; ++i)
      cout << ans[i] << '\n';
  }

  return 0;
}
