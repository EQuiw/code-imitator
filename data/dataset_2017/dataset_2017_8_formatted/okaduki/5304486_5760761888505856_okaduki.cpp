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

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int T;
  cin >> T;
  FOR(t_, 1, T + 1) {
    int H, W;
    cin >> H >> W;
    VS vs(H);
    REP(y, H) cin >> vs[y];

    set<char> memo;
    REP(y, H) REP(x, W) {
      if (vs[y][x] != '?' && !memo.count(vs[y][x])) {
        memo.insert(vs[y][x]);

        int lx, rx, ty, by;
        for (lx = x - 1; lx >= 0; --lx)
          if (vs[y][lx] != '?')
            break;
        ++lx;
        for (rx = x + 1; rx < W; ++rx)
          if (vs[y][rx] != '?')
            break;

        for (ty = y - 1; ty >= 0; --ty) {
          bool ok = true;
          for (int xx = lx; xx < rx; ++xx) {
            if (vs[ty][xx] != '?')
              ok = false;
          }
          if (!ok)
            break;
        }
        ++ty;
        for (by = y + 1; by < H; ++by) {
          bool ok = true;
          for (int xx = lx; xx < rx; ++xx) {
            if (vs[by][xx] != '?')
              ok = false;
          }
          if (!ok)
            break;
        }

        FOR(yy, ty, by) FOR(xx, lx, rx) vs[yy][xx] = vs[y][x];
      }
    }

    cout << "Case #" << t_ << ":" << endl;
    REP(y, H) cout << vs[y] << endl;
  }

  return 0;
}
