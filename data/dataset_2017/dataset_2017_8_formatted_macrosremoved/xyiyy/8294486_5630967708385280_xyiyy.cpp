#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;

long double k[1010], s[1010];

int main() {
  ios::sync_with_stdio(0);
  freopen("1.in", "r", stdin);
  // freopen("1.out","w",stdout);
  int cas = 1;
  int t;
  cin >> t;
  while (t--) {
    cout << "Case #" << cas++ << ": ";
    long double d;
    int n;
    cin >> d >> n;
    for (int i = 0; i < n; i++) {
      cin >> k[i] >> s[i];
    }
    long double L = 0, R = 1e14;
    for (int i = 0; i < 10010; i++) {
      long double mid = (L + R) / 2.0;
      bool ok = true;
      for (int j = 0; j < n; j++) {
        if (mid <= s[j])
          continue;
        long double cost = k[j] / (mid - s[j]) * mid;
        if (cost - d < -1e-7)
          ok = false;
      }
      if (ok)
        L = mid;
      else
        R = mid;
    }
    cout << fixed << setprecision(6) << L << endl;
  }
  return 0;
}
