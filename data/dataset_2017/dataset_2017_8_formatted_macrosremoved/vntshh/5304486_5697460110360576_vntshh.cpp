#include <bits/stdc++.h>
using namespace std;

using namespace std;
typedef long double ldb;
typedef long long lld;
lld powm(lld base, lld exp, lld mod = 1000000007) {
  lld ans = 1;
  while (exp) {
    if (exp & 1)
      ans = (ans * base) % mod;
    exp >>= 1, base = (base * base) % mod;
  }
  return ans;
}
typedef vector<lld> vlld;
typedef pair<lld, lld> plld;
typedef map<lld, lld> mlld;
typedef set<lld> slld;

const int MAXN = (1 << 16);
lld r[55], q[55][55], dp[MAXN];
lld check(lld x, lld y) {
  ldb a1 = floor((ldb)(10 * x) / (9 * r[0]));
  ldb a2 = floor((ldb)(10 * y) / (9 * r[1]));
  ldb a3 = ceil((ldb)(10 * x) / (11 * r[0]));
  ldb a4 = ceil((ldb)(10 * y) / (11 * r[1]));
  ldb m1 = min(a1, a2), m2 = max(a3, a4);

  // cout<<x<<" "<<y<<" "<<r[0]<<" "<<r[1]<<" "<<a1<<" "<<a2<<" "<<a3<<"
  // "<<a4<<endl;
  return (m2 <= m1);
}
int main() {
  freopen("234.in", "r", stdin);
  freopen("234.out", "w", stdout);
  lld t, n, p;
  cin >> t;
  for (lld tt = 1; tt < t + 1; tt++) {
    cin >> n >> p;
    for (lld i = 0; i < n; i++)
      cin >> r[i];
    for (lld i = 0; i < n; i++)
      for (lld j = 0; j < p; j++)
        cin >> q[i][j];
    for (lld i = 0; i < MAXN; i++)
      dp[i] = 0;
    cout << "Case #" << tt << ": ";
    if (n == 1) {
      lld cnt = 0;
      for (lld i = 0; i < p; i++) {
        ldb a1 = floor((ldb)(10 * q[0][i]) / (9 * r[0]));
        ldb a2 = ceil((ldb)(10 * q[0][i]) / (11 * r[0]));
        cnt += (lld)(a2 <= a1);
      }
      cout << cnt << endl;
    } else if (n == 2) {
      lld mask = (1 << (2 * p));
      for (lld i = 0; i < mask; i++) {
        for (lld j = 0; j < p; j++)
          for (lld k = p; k < 2 * p; k++) {
            if (i & (1 << j))
              if (i & (1 << k)) {
                dp[i] = max(dp[i], check(q[0][j], q[1][k - p]) +
                                       dp[i ^ (1 << j) ^ (1 << k)]);
              }
          }
      }
      cout << dp[mask - 1] << endl;
    }
  }
  return 0;
}
