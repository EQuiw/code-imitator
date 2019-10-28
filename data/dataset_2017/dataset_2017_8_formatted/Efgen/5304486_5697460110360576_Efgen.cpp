// @formatter:off
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<vector<int>> vvi;
typedef vector<ll> vl;
typedef vector<vector<ll>> vvl;
#define forn(i, n) for (int i = 0; i < (n); ++i)
#define forv(i, v) forn(i, sz(v))
#define all(v) v.begin(), v.end()
#define mp make_pair
#define pb push_back
#define X first
#define Y second
template <class T> inline T sqr(T x) { return x * x; }
template <class T> inline T parse(const string &s) {
  T x;
  stringstream ss(s);
  ss >> x;
  return x;
}
int gcd(int a, int b) { return a ? gcd(b % a, a) : b; }
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll powmod(ll a, ll p, ll m) {
  ll r = 1;
  while (p) {
    if (p & 1)
      r = r * a % m;
    p >>= 1;
    a = a * a % m;
  }
  return r;
}
// @formatter:on

int g1(int x, int r) {
  x *= 10;
  r *= 11;
  return (x + r - 1) / r;
}

int g2(int x, int r) {
  x *= 10;
  r *= 9;
  return x / r;
}

bool intresect(int x1, int y1, int x2, int y2) {
  if (x1 > x2) {
    swap(x1, x2);
    swap(y1, y2);
  }
  if (x1 == x2 && x1 == 0)
    return false;
  return x2 <= y1;
}

void solveTest() {
  int n, m;
  cin >> n >> m;
  vi r(n);
  forn(i, n) cin >> r[i];
  vector<vector<pii>> a(n, vector<pii>(m));
  forn(i, n) {
    forn(j, m) {
      int x;
      cin >> x;
      int x1 = g1(x, r[i]);
      int x2 = g2(x, r[i]);
      if (x1 <= x2) {
        a[i][j].X = x1;
        a[i][j].Y = x2;
      }
    }
  }
  int res = 0;
  if (n == 2) {
    sort(all(a[1]));
    do {
      int cnt = 0;
      forn(i, m) {
        if (intresect(a[0][i].X, a[0][i].Y, a[1][i].X, a[1][i].Y))
          cnt++;
      }
      if (cnt > res)
        res = cnt;
    } while (next_permutation(all(a[1])));
  } else {
    if (n == 1) {
      forn(i, m) {
        if (a[0][i].X || a[0][i].Y)
          res++;
      }
    }
  }

  cout << res;
}

int main() {
#ifdef EFGEN_DBG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int tests;
  cin >> tests;
  for (int test = 1; test <= tests; test++) {
    cout << "Case #" << test << ": ";
    solveTest();
    cout << endl;
  }
}
