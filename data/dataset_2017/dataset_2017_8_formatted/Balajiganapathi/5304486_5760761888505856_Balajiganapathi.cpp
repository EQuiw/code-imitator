/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
//#   define TRACE
#define TEST
#else
#define NDEBUG
//#   define FAST
#endif

#include <bits/stdc++.h>

using namespace std;

/* aliases */
using vi = vector<int>;
using pi = pair<int, int>;
using ll = long long int;

/* shortcut macros */
#define mp make_pair
#define fi first
#define se second
#define mt make_tuple
#define gt(t, i) get<i>(t)
#define all(x) (x).begin(), (x).end()
#define ini(a, v) memset(a, v, sizeof(a))
#define rep(i, s, n) for (int i = (s), _##i = (n); i <= _##i; ++i)
#define re(i, s, n) rep(i, (s), (n)-1)
#define fo(i, n) re(i, 0, n)
#define si(x) (int((x).size()))
#define is1(mask, i) (((mask) >> i) & 1)

/* trace macro */
#ifdef TRACE
#define trace(v...)                                                            \
  {                                                                            \
    cerr << __func__ << ":" << __LINE__ << ": ";                               \
    _dt(#v, v);                                                                \
  }
#else
#define trace(...)
#endif

#ifdef TRACE
pi _gp(string s) {
  pi r(0, si(s) - 1);
  int p = 0, s1 = 0, s2 = 0, start = 1;
  fo(i, si(s)) {
    int x = (s1 | s2);
    if (s[i] == ' ' && start) {
      ++r.fi;
    } else {
      start = 0;
      if (s[i] == ',' && !p && !x) {
        r.se = i - 1;
        return r;
      }
      if (x && s[i] == '\\')
        ++i;
      else if (!x && s[i] == '(')
        ++p;
      else if (!x && s[i] == ')')
        --p;
      else if (!s2 && s[i] == '\'')
        s1 ^= 1;
      else if (!s1 && s[i] == '"')
        s2 ^= 1;
    }
  }
  return r;
}

template <typename H> void _dt(string u, H &&v) {
  pi p = _gp(u);
  cerr << u.substr(p.fi, p.se - p.fi + 1) << " = " << forward<H>(v) << " |"
       << endl;
}

template <typename H, typename... T> void _dt(string u, H &&v, T &&... r) {
  pi p = _gp(u);
  cerr << u.substr(p.fi, p.se - p.fi + 1) << " = " << forward<H>(v) << " | ";
  _dt(u.substr(p.se + 2), forward<T>(r)...);
}

template <typename T>
ostream &operator<<(ostream &o, vector<T> v) { // print a vector
  o << "[";
  fo(i, si(v) - 1) o << v[i] << ", ";
  if (si(v))
    o << v.back();
  o << "]";
  return o;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &o, map<T1, T2> m) { // print a map
  o << "{";
  for (auto &p : m) {
    o << " (" << p.fi << " -> " << p.se << ")";
  }
  o << " }";
  return o;
}

template <typename T> ostream &operator<<(ostream &o, set<T> s) { // print a set
  o << "{";
  bool first = true;
  for (auto &entry : s) {
    if (!first)
      o << ", ";

    o << entry;
    first = false;
  }
  o << "}";
  return o;
}

template <size_t n, typename... T>
typename enable_if<(n >= sizeof...(T))>::type print_tuple(ostream &,
                                                          const tuple<T...> &) {
}

template <size_t n, typename... T>
typename enable_if<(n < sizeof...(T))>::type
print_tuple(ostream &os, const tuple<T...> &tup) {
  if (n != 0)
    os << ", ";
  os << get<n>(tup);
  print_tuple<n + 1>(os, tup);
}

template <typename... T>
ostream &operator<<(ostream &os, const tuple<T...> &tup) { // print a tuple
  os << "(";
  print_tuple<0>(os, tup);
  return os << ")";
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) { // print a pair
  return os << "(" << p.fi << ", " << p.se << ")";
}
#endif

/* util functions */
template <typename T1, typename T2, typename T3>
T1 modpow(T1 _a, T2 p, T3 mod) {
  assert(p >= 0);
  ll ret = 1, a = _a;

#ifndef FAST
  if (a < 0) {
    a %= mod;
    a += mod;
  }

  if (a >= mod) {
    a %= mod;
  }
#endif

  for (; p > 0; p /= 2) {
    if (p & 1)
      ret = ret * a % mod;
    a = a * a % mod;
  }

  return ret;
}

#define x1 _asdfzx1
#define y1 _ysfdzy1

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
  fo(i1, r) fo(j1, c) re(i2, i1, r) re(j2, j1, c) {
    can[i1][j1][i2][j2] = -1;
    pmask[i1][j1][i2][j2] = 0;
    rep(i, i1, i2) rep(j, j1, j2) {
      if (cake[i][j] != '?') {
        if (can[i1][j1][i2][j2] == -1)
          can[i1][j1][i2][j2] = cake[i][j];
        else
          can[i1][j1][i2][j2] = -1;
      }
      pmask[i1][j1][i2][j2] |= (1 << (i * c + j));
    }
    trace(i1, j1, i2, j2, can[i1][j1][i2][j2]);
  }
}

int solve(int mask) {
  int &ret = dp[mask];
  if (ret != -1)
    return ret;
  if (mask == (1 << (r * c)) - 1)
    return ret = 1;

  ret = 0;
  fo(i1, r) fo(j1, c) {
    if (ret)
      break;
    re(i2, i1, r) re(j2, j1, c) {
      if (ret)
        break;
      if ((mask & pmask[i1][j1][i2][j2]) == 0 && can[i1][j1][i2][j2] != -1) {
        int nmask = mask | pmask[i1][j1][i2][j2];
        if (solve(nmask)) {
          prv[nmask] = mask;
          prvi[nmask] = can[i1][j1][i2][j2];
          trace(nmask, prv[nmask], prvi[nmask]);
          ret = 1;
          break;
        }
      }
    }
  }

  trace(mask, ret);
  return ret;
}

void getAns() {
  int cur = (1 << (r * c)) - 1;
  fo(i, r) ans[i] = string(c, '?');
  while (cur > 0) {
    int nxt = (cur ^ prv[cur]);
    trace(cur, nxt, prvi[cur]);
    assert(prvi[cur]);
    fo(k, r * c) if (is1(nxt, k)) { ans[k / c][k % c] = prvi[cur]; }
    cur ^= nxt;
  }
}

int main() {
  ini(can, -1);
  int t;
  cin >> t;
  rep(kase, 1, t) {
    cin >> r >> c;
    fo(i, r) cin >> cake[i];
    // fo(i, r) trace(i, cake[i]);
    ini(dp, -1);
    init();
    assert(solve(0));
    getAns();

    cout << "Case #" << kase << ":\n";
    fo(i, r) cout << ans[i] << '\n';
  }

  return 0;
}
