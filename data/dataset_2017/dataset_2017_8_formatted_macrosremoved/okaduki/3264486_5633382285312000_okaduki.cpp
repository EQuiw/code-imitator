#include <bits/stdc++.h>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;
using PII = pair<int, int>;
using LL = long long;
using VL = vector<LL>;
using VVL = vector<VL>;
using PLL = pair<LL, LL>;
using VS = vector<string>;
template <class S, class T> istream &operator>>(istream &is, pair<S, T> &p) {
  return is >> p.first >> p.second;
}
template <class S, class T>
ostream &operator<<(ostream &os, const pair<S, T> &p) {
  return os << p.first << " " << p.second;
}
template <class T> void maxi(T &x, T y) {
  if (x < y)
    x = y;
}
template <class T> void mini(T &x, T y) {
  if (x > y)
    x = y;
}

const double EPS = 1e-10;
const double PI = acos(-1.0);
const LL MOD = 1e9 + 7;

bool istidy(LL x) {
  int prv = 10;
  while (x > 0) {
    if (prv < x % 10)
      return false;
    prv = x % 10;
    x /= 10;
  }
  return true;
}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int t = (1); t < (T + 1); ++t) {
    LL N;
    cin >> N;
    LL ans = 0;
    for (ans = N; ans > 0; --ans)
      if (istidy(ans))
        break;

    cout << "Case #" << t << ": " << ans << endl;
  }

  return 0;
}
