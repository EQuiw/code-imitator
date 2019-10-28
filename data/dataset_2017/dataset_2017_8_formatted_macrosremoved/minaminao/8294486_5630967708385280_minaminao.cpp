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

template <class T, class... Tail>
void tied_sort(vector<T> &a, vector<Tail> &... tail) {
  long long n = a.size();
  using S = tuple<T, Tail...>;
  vector<S> s(n);
  for (long long i = 0; i < n; i++)
    s[i] = make_tuple(a[i], tail[i]...);
  sort(s.begin(), s.end());
  for (long long i = 0; i < n; i++)
    tie(a[i], tail[i]...) = s[i];
}

signed main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  freopen("A-small-attempt1.in", "r", stdin);
  freopen("A-small-attempt1.txt", "w", stdout);
  // freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
  long long T;
  cin >> T;
  cout << fixed << setprecision(10);
  for (long long t = 0; t < T; t++) {
    double D;
    long long N;
    cin >> D >> N;
    if (N > 2)
      break;
    vector<double> K(N), S(N);
    for (long long i = (0); i < (N); i++) {
      cin >> K[i] >> S[i];
    }
    tied_sort(K, S);
    ;
    double totaltime = 0;
    for (long long i = (0); i < (N - 1); i++) {
      double mint = INF;
      long long minid = -1;
      for (long long j = (0); j < (N - 1); j++) {
        if (K[j] > D)
          break;
        if (S[i + 1] > S[i])
          continue;
        double time = (K[i + 1] - K[i]) / (S[i] - S[i + 1]);
        if (K[j] + S[j] * time > D)
          continue;
        if (chmin(mint, time)) {
          minid = j;
        }
      }
      if (minid == -1) {
        break;
      }
      for (long long j = (0); j < (N); j++) {
        K[j] += S[j] * mint;
      }
      S[minid] = S[minid + 1];
      totaltime += mint;
    }
    double ans = 0;
    totaltime += (D - K[0]) / S[0];
    ans += D / totaltime;
    cout << "Case #" << t + 1 << ": " << ans << endl;
  }
  return 0;
}
