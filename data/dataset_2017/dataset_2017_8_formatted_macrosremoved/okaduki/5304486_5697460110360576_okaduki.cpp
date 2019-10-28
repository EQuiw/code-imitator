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
    int N, P;
    cin >> N >> P;
    VL rs(N);
    for (int i = (0); i < (N); ++i)
      cin >> rs[i];
    VVL qs(N, VL(P));
    for (int i = (0); i < (N); ++i) {
      for (int j = (0); j < (P); ++j)
        cin >> qs[i][j];
      sort(begin(((qs[i]))), end(((qs[i]))));
    }

    LL ans = 0;
    if (N == 1) {
      for (int i = (0); i < (P); ++i) {
        int lb_k = ceil(qs[0][i] * 1. / (rs[0] * 1.1));
        int ub_k = floor(qs[0][i] * 1. / (rs[0] * 0.9));
        if (lb_k <= ub_k)
          ++ans;
      }
    } else {
      int i2 = 0;
      for (int i1 = (0); i1 < (P); ++i1) {
        int lb_k = ceil(qs[0][i1] * 1. / (rs[0] * 1.1));
        int ub_k = floor(qs[0][i1] * 1. / (rs[0] * 0.9));

        while (i2 < P) {
          int lb2_k = (int)ceil(qs[1][i2] * 1. / (rs[1] * 1.1));
          int ub2_k = (int)floor(qs[1][i2] * 1. / (rs[1] * 0.9));
          if (lb_k <= ub2_k && lb2_k <= ub_k) {
            ++ans;
            ++i2;
            break;
          } else if (ub_k < lb2_k) {
            break;
          }
          ++i2;
        }
      }
    }

    cout << "Case #" << t_ << ": " << ans << endl;
  }

  return 0;
}
