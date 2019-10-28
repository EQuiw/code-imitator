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

pair<lld, char> a[3];
int main() {
  freopen("5.in", "r", stdin);
  freopen("6.out", "w", stdout);
  lld t, n, r, o, y, g, b, v;
  cin >> t;
  for (lld tt = 1; tt < t + 1; tt++) {
    cin >> n >> r >> o >> y >> g >> b >> v;
    lld curr = 0, sz = 0, flag = 0;
    string ans = "";
    a[0] = {r, 'R'};
    a[1] = {y, 'Y'};
    a[2] = {b, 'B'};
    sort(a, a + 3), reverse(a, a + 3);
    while (1) {
      // cout<<ans<<" "<<curr<<" "<<sz<<" "<<ans[sz]<<endl;
      if (a[curr].first) {
        if (!sz or ans[sz - 1] != a[curr].second)
          ans += a[curr].second, sz++, a[curr].first--, curr = (curr + 1) % 3;
        else {
          flag = 1;
          break;
        }
      } else
        curr = (curr + 1) % 3;
      if (a[0].first == 0 and a[1].first == 0 and a[2].first == 0)
        break;
    }
    cout << "Case #" << tt << ": ";
    if (flag == 0)
      cout << ans << endl;
    else
      cout << "IMPOSSIBLE\n";
  }
  return 0;
}
