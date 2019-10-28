#include "bits/stdc++.h"
using namespace std;
#ifdef _DEBUG
#include "dump.hpp"
#else
#define dump(...)
#endif

#define int long long
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define rrep(i, a, b) for (int i = (b)-1; i >= (a); i--)
#define all(c) begin(c), end(c)
const int INF =
    sizeof(int) == sizeof(long long) ? 0x3f3f3f3f3f3f3f3fLL : 0x3f3f3f3f;
const int MOD = (int)(1e9) + 7;
template <class T> bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
template <class T> bool chmin(T &a, const T &b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}

signed main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.txt", "w", stdout);
  // freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int R, C;
    cin >> R >> C;
    vector<vector<char>> v(R, vector<char>(C));
    rep(i, 0, R) rep(j, 0, C) { cin >> v[i][j]; }
    rep(i, 0, R) rep(j, 1, C) {
      if (v[i][j] == '?') {
        v[i][j] = v[i][j - 1];
      }
    }
    rep(i, 0, R) rrep(j, 0, C - 1) {
      if (v[i][j] == '?') {
        v[i][j] = v[i][j + 1];
      }
    }
    rep(i, 1, R) {
      if (v[i][0] == '?') {
        rep(j, 0, C) { v[i][j] = v[i - 1][j]; }
      }
    }
    rrep(i, 0, R - 1) {
      if (v[i][0] == '?') {
        rep(j, 0, C) { v[i][j] = v[i + 1][j]; }
      }
    }
    cout << "Case #" << t + 1 << ":" << endl;
    rep(i, 0, v.size()) {
      cout << v[i][0];
      rep(j, 1, v[i].size()) { cout << v[i][j]; }
      cout << endl;
    }
  }
  return 0;
}