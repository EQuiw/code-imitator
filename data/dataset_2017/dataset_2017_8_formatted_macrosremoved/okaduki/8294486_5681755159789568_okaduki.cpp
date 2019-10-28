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
const double INF = 1e15;

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int t_ = (1); t_ < (T + 1); ++t_) {
    int N, Q;
    cin >> N >> Q;
    vector<PLL> es(N);
    for (int i = (0); i < (N); ++i)
      cin >> es[i];

    VVL dist(N, VL(N));
    for (int i = (0); i < (N); ++i)
      for (int j = (0); j < (N); ++j)
        cin >> dist[i][j];

    while (Q--) {
      int U, V;
      cin >> U >> V;
      --U;
      --V;

      vector<LL> acc(N);
      for (int i = N - 2; i >= 0; --i)
        acc[i] = dist[i][i + 1] + acc[i + 1];

      vector<double> dp(N + 1, INF);
      dp[N - 1] = 0;
      for (int i = N - 2; i >= 0; --i) {
        for (int j = i + 1; j < N; ++j) {
          if (acc[i] - acc[j] > es[i].first)
            break;
          mini(dp[i], dp[j] + (acc[i] - acc[j]) * 1. / es[i].second);
        }
      }
      double ans = dp[0];
      cout << "Case #" << t_ << ": " << fixed << setprecision(9) << ans << endl;
    }
  }

  return 0;
}
