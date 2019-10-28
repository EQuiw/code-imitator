#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll, ll>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-9;
int main() {
  ios::sync_with_stdio(false);
  ll TC;
  cin >> TC;
  for (ll tc = (1); tc < (TC + 1); tc++) {
    double d, n;
    cin >> d >> n;
    vl k(n), s(n);
    double a = 0;
    for (ll i = (0); i < (n); i++) {
      cin >> k[i] >> s[i];
      a = max(a, (d - k[i]) / s[i]);
    }
    cout << "Case #" << tc << ": " << setprecision(8) << fixed << d / a << endl;
  }
}
