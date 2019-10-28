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
    int H, W;
    cin >> H >> W;
    VS vs(H);
    for (int y = (0); y < (H); ++y)
      cin >> vs[y];

    set<char> memo;
    for (int y = (0); y < (H); ++y)
      for (int x = (0); x < (W); ++x) {
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

          for (int yy = (ty); yy < (by); ++yy)
            for (int xx = (lx); xx < (rx); ++xx)
              vs[yy][xx] = vs[y][x];
        }
      }

    cout << "Case #" << t_ << ":" << endl;
    for (int y = (0); y < (H); ++y)
      cout << vs[y] << endl;
  }

  return 0;
}
