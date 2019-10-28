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
#define UNIQ(c) (c).erase(unique(ALL((c))), end((c)))

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

bool check(VI tmp, const string &s) {
  string col = "ROYGB";
  for (int i = 0; i < SZ(s); ++i) {
    int ix = col.find(s[i]);
    tmp[ix]--;
  }
  REP(i, 6) if (tmp[i] != 0) return false;

  if (s[0] == s.back())
    return false;
  REP(i, SZ(s) - 1)
  if (s[i] == s[i + 1])
    return false;
  return true;
}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int T;
  cin >> T;
  FOR(t, 1, T + 1) {
    int N;
    string col = "ROYGB";
    VI xs(6);
    cin >> N;
    // R,O,Y,G,B,V;
    REP(i, 6) cin >> xs[i];
    VI orig = xs;

    int mx = max(xs[0], max(xs[1 * 2], xs[2 * 2]));
    bool ok = (mx <= N - mx);

    if (!ok) {
      cout << "Case #" << t << ": IMPOSSIBLE" << endl;
    } else {
      string ans(N, '*');
      int ix = -1;
      REP(i, 6) if (xs[i] == mx) ix = i;

      REP(i, 6) if (i != ix && xs[i]) {
        ans[0] = col[i];
        xs[i]--;
        ix = i;
        break;
      }
      for (int i = 1; i < N; ++i) {
        int mix = -1;
        REP(j, 6) {
          if ((mix == -1 || xs[mix] < xs[j]) && j != ix)
            mix = j;
        }
        ans[i] = col[mix];
        xs[mix]--;
        ix = mix;
      }

      if (!check(orig, ans)) {
        REP(i, 6) cout << orig[i] << " ";
        cout << endl;
        cout << ans << endl;
        return 1;
      }

      cout << "Case #" << t << ": " << ans << endl;
    }
  }

  return 0;
}
