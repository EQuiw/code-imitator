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

lld k[100005], second[100005];
int main() {
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
  lld t, n, d;
  ldb ans;
  cin >> t;
  for (lld tt = 1; tt < t + 1; tt++) {
    cin >> d >> n, ans = 1000111000111000111LL;
    for (lld i = 1; i < n + 1; i++)
      cin >> k[i] >> second[i],
          ans = min(ans, ((ldb)(d * second[i]) / (d - k[i])));
    cout << "Case #" << tt << ": " << fixed << setprecision(7) << ans << endl;
  }
  return 0;
}
