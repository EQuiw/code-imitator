#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<double, int> PDI;
const double eps = 1e-8;
const double pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
const int INF = 2e9 + 7;
const int mod = 1e9 + 7;
LL powmod(LL a, LL b) {
  LL res = 1;
  a %= mod;
  assert(b >= 0);
  for (; b; b >>= 1) {
    if (b & 1)
      res = res * a % mod;
    a = a * a % mod;
  }
  return res;
}

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, cas = 1, d, n, k, s;
  cin >> t;
  while (t--) {
    cin >> d >> n;
    double ans = 0;
    for (int i = 0; i < n; i++) {
      cin >> k >> s;
      ans = max(ans, (d - k) * 1.0 / s);
    }
    printf("Case #%d: %.6f\n", cas++, d / ans);
  }
  return 0;
}
