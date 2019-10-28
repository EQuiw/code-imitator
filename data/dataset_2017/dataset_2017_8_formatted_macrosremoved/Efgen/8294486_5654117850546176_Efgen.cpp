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

void solveTest() {
  int n, r, o, y, g, b, v;
  cin >> n >> r >> o >> y >> g >> b >> v;
  vector<pair<int, char>> a(3);
  a[0] = {r, 'R'};
  a[1] = {y, 'Y'};
  a[2] = {b, 'B'};
  sort(a.begin(), a.end());
  reverse(a.begin(), a.end());
  string ans;

  int rg = a[0].first - a[1].first;
  if (rg <= a[2].first) {
    int c1 = a[1].first + a[2].first - a[0].first;
    int c2 = a[0].first - a[2].first;
    int c3 = a[0].first - a[1].first;
    for (int i = 0; i < (c1); ++i) {
      cout << a[0].second << a[1].second << a[2].second;
    }
    for (int i = 0; i < (c2); ++i) {
      cout << a[0].second << a[1].second;
    }
    for (int i = 0; i < (c3); ++i) {
      cout << a[0].second << a[2].second;
    }

  } else {
    cout << "IMPOSSIBLE";
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
