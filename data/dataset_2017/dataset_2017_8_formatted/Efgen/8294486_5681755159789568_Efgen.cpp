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
const ll inf = 1000000000000000000LL;
const double dinf = 1e+100;

void solveTest() {
  int n, q;
  cin >> n >> q;
  vi E(n), S(n);
  forn(i, n) { cin >> E[i] >> S[i]; }
  vvl a(n, vl(n));
  vvl b(n, vl(n));
  forn(i, n) {
    forn(j, n) {
      cin >> a[i][j];
      if (a[i][j] == -1)
        a[i][j] = inf;
      if (i == j)
        a[i][i] = 0;
      b[i][j] = a[i][j];
    }
  }
  forn(k, n) {
    forn(i, n) {
      forn(j, n) { a[i][j] = min(a[i][j], a[i][k] + a[k][j]); }
    }
  }

  forn(qq, q) {
    int s, t;
    cin >> s >> t;
    s--;
    t--;
    vector<double> d(n);
    vector<bool> mark(n);
    forn(i, n) d[i] = dinf;
    d[s] = 0;
    forn(i, n) {
      int v = -1;
      forn(j, n) {
        if (!mark[j] && (v < 0 || d[j] < d[v]))
          v = j;
      }
      if (v < 0 || v == t)
        break;
      mark[v] = true;
      forn(j, n) {
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
