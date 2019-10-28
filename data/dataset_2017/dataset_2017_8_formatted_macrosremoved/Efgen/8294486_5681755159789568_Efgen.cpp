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
const ll inf = 1000000000000000000LL;
const double dinf = 1e+100;

void solveTest() {
  int n, q;
  cin >> n >> q;
  vi E(n), S(n);
  for (int i = 0; i < (n); ++i) {
    cin >> E[i] >> S[i];
  }
  vvl a(n, vl(n));
  vvl b(n, vl(n));
  for (int i = 0; i < (n); ++i) {
    for (int j = 0; j < (n); ++j) {
      cin >> a[i][j];
      if (a[i][j] == -1)
        a[i][j] = inf;
      if (i == j)
        a[i][i] = 0;
      b[i][j] = a[i][j];
    }
  }
  for (int k = 0; k < (n); ++k) {
    for (int i = 0; i < (n); ++i) {
      for (int j = 0; j < (n); ++j) {
        a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
      }
    }
  }

  for (int qq = 0; qq < (q); ++qq) {
    int s, t;
    cin >> s >> t;
    s--;
    t--;
    vector<double> d(n);
    vector<bool> mark(n);
    for (int i = 0; i < (n); ++i)
      d[i] = dinf;
    d[s] = 0;
    for (int i = 0; i < (n); ++i) {
      int v = -1;
      for (int j = 0; j < (n); ++j) {
        if (!mark[j] && (v < 0 || d[j] < d[v]))
          v = j;
      }
      if (v < 0 || v == t)
        break;
      mark[v] = true;
      for (int j = 0; j < (n); ++j) {
        if (!mark[j]) {
          double dist = a[v][j];
          if (dist > E[v])
            continue;
          d[j] = min(d[j], d[v] + dist / S[v]);
        }
      }
    }
    if (qq)
      printf(" ");
    printf("%0.10lf", d[t]);
  }
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
