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

bool check(VI tmp, const string &s) {
  string col = "ROYGB";
  for (int i = 0; i < int((s).size()); ++i) {
    int ix = col.find(s[i]);
    tmp[ix]--;
  }
  for (int i = (0); i < (6); ++i)
    if (tmp[i] != 0)
      return false;

  if (s[0] == s.back())
    return false;
  for (int i = (0); i < (int((s).size()) - 1); ++i)
    if (s[i] == s[i + 1])
      return false;
  return true;
}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int t = (1); t < (T + 1); ++t) {
    int N;
    string col = "ROYGB";
    VI xs(6);
    cin >> N;
    // R,O,Y,G,B,V;
    for (int i = (0); i < (6); ++i)
      cin >> xs[i];
    VI orig = xs;

    int mx = max(xs[0], max(xs[1 * 2], xs[2 * 2]));
    bool ok = (mx <= N - mx);

    if (!ok) {
      cout << "Case #" << t << ": IMPOSSIBLE" << endl;
    } else {
      string ans(N, '*');
      int ix = -1;
      for (int i = (0); i < (6); ++i)
        if (xs[i] == mx)
          ix = i;

      for (int i = (0); i < (6); ++i)
        if (i != ix && xs[i]) {
          ans[0] = col[i];
          xs[i]--;
          ix = i;
          break;
        }
      for (int i = 1; i < N; ++i) {
        int mix = -1;
        for (int j = (0); j < (6); ++j) {
          if ((mix == -1 || xs[mix] < xs[j]) && j != ix)
            mix = j;
        }
        ans[i] = col[mix];
        xs[mix]--;
        ix = mix;
      }

      if (!check(orig, ans)) {
        for (int i = (0); i < (6); ++i)
          cout << orig[i] << " ";
        cout << endl;
        cout << ans << endl;
        return 1;
      }

      cout << "Case #" << t << ": " << ans << endl;
    }
  }

  return 0;
}
