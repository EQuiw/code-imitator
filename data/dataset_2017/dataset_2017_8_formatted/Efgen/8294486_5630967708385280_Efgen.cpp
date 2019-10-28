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

void solveTest() {
  int d, n;
  cin >> d >> n;
  vi pos(n);
  vi v(n);
  forn(i, n) { cin >> pos[i] >> v[i]; }
  double l = 0, r = 1e+14;
  forn(it, 200) {
    double mv = (l + r) / 2;
    bool ok = true;
    forn(i, n) {

      if (mv > v[i]) {
        double t = pos[i] / (mv - v[i]);
        if (t * mv < d) {
          ok = false;
          break;
        }
      }
    }
    if (ok)
      l = mv;
    else
      r = mv;
  }
  printf("%0.10lf", l);
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
