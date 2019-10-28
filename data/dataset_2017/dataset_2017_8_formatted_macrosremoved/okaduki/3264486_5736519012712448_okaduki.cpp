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
  for (int t = (1); t < (T + 1); ++t) {
    string S;
    cin >> S;
    int K;
    cin >> K;
    int N = int((S).size());
    VI xs(N);
    for (int i = (0); i < (N); ++i)
      xs[i] = S[i] == '+';

    int ans = 0;
    for (int i = 0; i + K <= N; ++i) {
      if (!xs[i]) {
        ++ans;
        for (int k = (0); k < (K); ++k)
          xs[i + k] = !xs[i + k];
      }
    }
    if (accumulate(begin((xs)), end((xs)), 0) != N)
      cout << "Case #" << t << ": IMPOSSIBLE" << endl;
    else
      cout << "Case #" << t << ": " << ans << endl;
  }

  return 0;
}
