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
constexpr int mx_n = 1003, mx_c = 6;

int c[mx_c], n;
char col[] = "ROYGBV";
map<int, char> cache[mx_n][mx_n][3];
map<int, char> nxt[mx_n][mx_n][3];
int s;

char solve(int r, int y, int b, int l) {
  int tot = r + y + b;
  if (tot == 0)
    return l != s;
  if (max(r, max(y, b)) > (tot + 1) / 2 + 1)
    return 0;
  auto it = cache[r][y][l].find(b);
  if (it != cache[r][y][l].end())
    return it->second;
  char &ret = cache[r][y][l][b];
  ret = 0;

  if (l != 0 && r > 0 && solve(r - 1, y, b, 0)) {
    ret = 1;
    nxt[r][y][l][b] = 0;
  } else if (l != 1 && y > 0 && solve(r, y - 1, b, 1)) {
    ret = 1;
    nxt[r][y][l][b] = 1;
  } else if (l != 2 && b > 0 && solve(r, y, b - 1, 2)) {
    ret = 1;
    nxt[r][y][l][b] = 2;
  }

  return ret;
}

string solve() {
  for (int i = ((0)), _i = ((mx_n)-1); i <= _i; ++i)
    for (int j = ((0)), _j = ((mx_n)-1); j <= _j; ++j)
      for (int k = ((0)), _k = ((3) - 1); k <= _k; ++k)
        cache[i][j][k].clear(), nxt[i][j][k].clear();
  for (int i = ((0)), _i = ((3) - 1); i <= _i; ++i)
    if (c[2 * i]) {
      s = i;
      break;
    }

  --c[2 * s];
  if (!solve(c[0], c[2], c[4], s))
    return "IMPOSSIBLE";

  string ans;
  ans += col[2 * s];
  int cc[3] = {c[0], c[2], c[4]};
  int l = s;
  for (int i = ((1)), _i = ((n)-1); i <= _i; ++i) {
    int nx = nxt[cc[0]][cc[1]][l][cc[2]];
    ans += col[2 * nx];
    l = nx;
    --cc[nx];
  }
  ++c[2 * s];

  return ans;
}

int main() {
  int _t;
  cin >> _t;
  for (int kase = (1), _kase = (_t); kase <= _kase; ++kase) {
    cin >> n;
    for (int i = ((0)), _i = ((mx_c)-1); i <= _i; ++i)
      cin >> c[i];

    string ans = "IMPOSSIBLE";
    ans = solve();

    cout << "Case #" << kase << ": " << ans << endl;
  }

  return 0;
}
