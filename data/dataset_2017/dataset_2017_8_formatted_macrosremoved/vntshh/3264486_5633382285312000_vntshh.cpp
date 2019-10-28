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

int main() {
  freopen("done3.in", "r", stdin);
  freopen("done3.out", "w", stdout);
  lld t, k, ans;
  string x;
  cin >> t;
  for (lld tt = 1; tt < t + 1; tt++) {
    cin >> x, k = lld((x).size());
    for (lld i = k - 2; i >= 0; i--)
      if (x[i] > x[i + 1]) {
        x[i]--;
        for (lld j = i + 1; j < k; j++)
          x[j] = '9';
      }
    ans = stoll(x);
    cout << "Case #" << tt << ": " << ans << endl;
  }
  return 0;
}
