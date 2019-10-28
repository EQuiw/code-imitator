#include "bits/stdc++.h"
using namespace std;
const long long INF =
    sizeof(long long) == sizeof(long long) ? 0x3f3f3f3f3f3f3f3fLL : 0x3f3f3f3f;
const long long MOD = (long long)(1e9) + 7;
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
  long long T;
  cin >> T;
  for (long long t = 0; t < T; t++) {
    long long R, C;
    cin >> R >> C;
    vector<vector<char>> v(R, vector<char>(C));
    for (long long i = (0); i < (R); i++)
      for (long long j = (0); j < (C); j++) {
        cin >> v[i][j];
      }
    for (long long i = (0); i < (R); i++)
      for (long long j = (1); j < (C); j++) {
        if (v[i][j] == '?') {
          v[i][j] = v[i][j - 1];
        }
      }
    for (long long i = (0); i < (R); i++)
      for (long long j = (C - 1) - 1; j >= (0); j--) {
        if (v[i][j] == '?') {
          v[i][j] = v[i][j + 1];
        }
      }
    for (long long i = (1); i < (R); i++) {
      if (v[i][0] == '?') {
        for (long long j = (0); j < (C); j++) {
          v[i][j] = v[i - 1][j];
        }
      }
    }
    for (long long i = (R - 1) - 1; i >= (0); i--) {
      if (v[i][0] == '?') {
        for (long long j = (0); j < (C); j++) {
          v[i][j] = v[i + 1][j];
        }
      }
    }
    cout << "Case #" << t + 1 << ":" << endl;
    for (long long i = (0); i < (v.size()); i++) {
      cout << v[i][0];
      for (long long j = (1); j < (v[i].size()); j++) {
        cout << v[i][j];
      }
      cout << endl;
    }
  }
  return 0;
}
