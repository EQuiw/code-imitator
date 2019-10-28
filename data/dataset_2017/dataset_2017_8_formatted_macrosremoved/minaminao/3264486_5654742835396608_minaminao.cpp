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
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("C-small-1-attempt0.txt", "w", stdout);
  long long T;
  cin >> T;
  for (long long t = 0; t < T; t++) {
    long long N;
    cin >> N;
    long long K;
    cin >> K;
    priority_queue<long long> pq;
    pq.emplace(N);
    for (long long k = (0); k < (K); k++) {
      long long a = pq.top();
      pq.pop();
      a--;
      long long b = a / 2, c = a - b;
      // dump(a, b, c);
      pq.emplace(b);
      pq.emplace(c);
      if (k == K - 1) {
        cout << "Case #" << t + 1 << ": ";
        cout << max(b, c) << " " << min(b, c) << endl;
      }
    }
  }
  return 0;
}
