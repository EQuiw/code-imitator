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
constexpr int mx = -1;
constexpr ll lim = 1000000000000000000L;
// constexpr ll lim = 100;

vector<ll> tidy;

void gen(ll num, int d) {
  // trace(num, d);
  if (num > 0)
    tidy.push_back(num);
  if (num <= lim / 10) {
    gen(num * 10 + d, d);
  }
  if (d < 9)
    gen(num, d + 1);
}

void pre() {
  gen(0, 1);
  sort((tidy).begin(), (tidy).end());
  // tidy.resize(unique(all(tidy)) - tidy.begin());
  // trace(tidy);
  ;
}

ll solve(ll n) {
  auto it = upper_bound((tidy).begin(), (tidy).end(), n) - 1;
  return *it;
}

int main() {
  pre();
  int _t;
  cin >> _t;
  for (int kase = (1), _kase = (_t); kase <= _kase; ++kase) {
    ll n;
    cin >> n;

    cout << "Case #" << kase << ": " << solve(n) << endl;
  }

  return 0;
}
