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
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.txt", "w", stdout);
  long long T;
  cin >> T;
  for (long long t = 0; t < T; t++) {

    long long N;
    cin >> N;
    string s = to_string(N);
    long long n = s.size();
    vector<long long> pow10(n);
    pow10[0] = 1;
    for (long long i = (0); i < (n - 1); i++)
      pow10[i + 1] = pow10[i] * 10;
    ;
    while (true) {
      long long m = 0;
      for (long long i = (1); i < (n); i++) {
        if (s[i - 1] <= s[i])
          m++;
        else
          break;
      };
      if (m == n - 1)
        break;
      N -= N % pow10[n - 1 - m];
      N--;
      ;
      s = to_string(N);
      n = s.size();
    }
    cout << "Case #" << t + 1 << ": ";
    cout << N << endl;

    // bool flag = true;
    // rep(i, 0, n)
    //	if (!v[i])
    //		flag = false;
    // cout << "Case #" << t + 1 << ": ";
    // if (flag) {
    //	cout << ans << endl;
    //}
    // else {
    //	cout << "IMPOSSIBLE" << endl;
    //}
  }
  return 0;
}
