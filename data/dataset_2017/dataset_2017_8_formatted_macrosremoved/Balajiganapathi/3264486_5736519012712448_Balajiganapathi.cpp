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

int main() {
  int _t;
  cin >> _t;
  for (int kase = (1), _kase = (_t); kase <= _kase; ++kase) {
    string cakes;
    int k;
    cin >> cakes >> k;
    // trace(cakes, k);

    int ret = 0;
    for (int i = ((0)), _i = (((int((cakes).size())) - k + 1) - 1); i <= _i;
         ++i) {
      if (cakes[i] == '-') {
        ++ret;
        for (int j = ((i)), _j = ((i + k) - 1); j <= _j; ++j)
          cakes[j] = (cakes[j] == '-' ? '+' : '-');
      }
      // trace(i, cakes, ret);
    }

    for (char c : cakes)
      if (c == '-')
        ret = -1;

    cout << "Case #" << kase << ": ";
    if (ret == -1)
      cout << "IMPOSSIBLE";
    else
      cout << ret;
    cout << endl;
  }

  return 0;
}
