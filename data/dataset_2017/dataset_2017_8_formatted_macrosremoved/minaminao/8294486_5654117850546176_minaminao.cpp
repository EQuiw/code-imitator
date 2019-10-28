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
  // freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
  long long T;
  cin >> T;
  cout << fixed << setprecision(10);
  for (long long t = 0; t < T; t++) {
    string ans;

    long long N;
    cin >> N;
    long long R, O, Y;
    cin >> R >> O >> Y;
    long long G, B, V;
    cin >> G >> B >> V;

    long long maxi = N / 2;
    if (R > maxi || Y > maxi || B > maxi) {
      ans = "IMPOSSIBLE";
    } else {
      using P = pair<long long, char>;
      vector<P> v;
      v.emplace_back(R, 'R');
      v.emplace_back(Y, 'Y');
      v.emplace_back(B, 'B');
      sort(begin(v), end(v));
      reverse(begin(v), end(v));
      vector<string> p;
      for (long long i = (0); i < (v[0].first); i++) {
        p.emplace_back(string(1, v[0].second));
      }
      long long cur = 0;
      for (long long i = (0); i < (v[1].first); i++) {
        p[(cur++) % p.size()] += v[1].second;
      }
      for (long long i = (0); i < (v[2].first); i++) {
        p[(cur++) % p.size()] += v[2].second;
      }
      // dump(p);
      for (long long i = (0); i < (p.size()); i++) {
        ans += p[i];
      }
    }
    cout << "Case #" << t + 1 << ": " << ans << endl;
  }
  return 0;
}
