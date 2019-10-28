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

pair<ll, ll> solve(ll len, ll k) {
  map<ll, ll> cnt;
  cnt[len] = 1;
  ll ck = 0;

  while (ck < k) {
    auto last = *cnt.rbegin();
    cnt.erase(last.first);
    ll mid = (last.first + 1) / 2;
    ll s1 = mid - 1, s2 = last.first - mid;
    // trace(last, mid, s1, s2, ck);
    if (ck + last.second < k) {
      ck += last.second;
      cnt[s1] += last.second;
      cnt[s2] += last.second;
    } else {
      return {min(s1, s2), max(s1, s2)};
    }
  }

  return {0, 0};
}

int main() {
  int _t;
  cin >> _t;
  for (int kase = (1), _kase = (_t); kase <= _kase; ++kase) {
    ll n, k;
    cin >> n >> k;
    auto ans = solve(n, k);

    cout << "Case #" << kase << ": " << ans.second << " " << ans.first << endl;
  }

  return 0;
}
