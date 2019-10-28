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

#define ALL(a) begin((a)), end((a))
#define RALL(a) (a).rbegin(), (a).rend()
#define PB push_back
#define EB emplace_back
#define MP make_pair
#define SZ(a) int((a).size())
#define SORT(c) sort(ALL((c)))
#define RSORT(c) sort(RALL((c)))

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)

#define FF first
#define SS second
template <class S, class T> istream &operator>>(istream &is, pair<S, T> &p) {
  return is >> p.FF >> p.SS;
}
template <class S, class T>
ostream &operator<<(ostream &os, const pair<S, T> &p) {
  return os << p.FF << " " << p.SS;
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
  FOR(t, 1, T + 1) {
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
