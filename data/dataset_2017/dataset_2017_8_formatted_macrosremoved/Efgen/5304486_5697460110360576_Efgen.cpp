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
  for (int i = 0; i < (n); ++i)
    cin >> r[i];
  vector<vector<pii>> a(n, vector<pii>(m));
  for (int i = 0; i < (n); ++i) {
    for (int j = 0; j < (m); ++j) {
      int x;
      cin >> x;
      int x1 = g1(x, r[i]);
      int x2 = g2(x, r[i]);
      if (x1 <= x2) {
        a[i][j].first = x1;
        a[i][j].second = x2;
      }
    }
  }
  int res = 0;
  if (n == 2) {
    sort(a[1].begin(), a[1].end());
    do {
      int cnt = 0;
      for (int i = 0; i < (m); ++i) {
        if (intresect(a[0][i].first, a[0][i].second, a[1][i].first,
                      a[1][i].second))
          cnt++;
      }
      if (cnt > res)
        res = cnt;
    } while (next_permutation(a[1].begin(), a[1].end()));
  } else {
    if (n == 1) {
      for (int i = 0; i < (m); ++i) {
        if (a[0][i].first || a[0][i].second)
          res++;
      }
    }
  }

  cout << res;
}

int main() {

  int tests;
  cin >> tests;
  for (int test = 1; test <= tests; test++) {
    cout << "Case #" << test << ": ";
    solveTest();
    cout << endl;
  }
}
