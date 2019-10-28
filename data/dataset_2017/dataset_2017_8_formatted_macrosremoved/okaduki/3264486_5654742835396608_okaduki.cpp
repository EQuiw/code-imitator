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

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int t_ = (1); t_ < (T + 1); ++t_) {
    LL N, K;
    cin >> N >> K;

    vector<bool> xs(N + 2);
    xs[0] = xs[N + 1] = true;
    tuple<LL, LL, LL> ans;
    for (int k = (0); k < (K); ++k) {
      tuple<LL, LL, LL> mx(-1, -1, -1);
      for (int i = (0); i < (N + 2); ++i) {
        if (xs[i])
          continue;
        LL l, r;
        for (l = i - 1; !xs[l]; --l)
          ;
        for (r = i + 1; !xs[r]; ++r)
          ;
        l = i - l - 1;
        r = r - i - 1;
        tuple<LL, LL, LL> t(min(l, r), max(l, r), -i);
        maxi(mx, t);
      }
      xs[-get<2>(mx)] = true;
      ans = mx;
    }
    cout << "Case #" << t_ << ": " << get<1>(ans) << " " << get<0>(ans) << endl;
  }

  return 0;
}
