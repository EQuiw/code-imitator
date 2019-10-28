#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define zero(x) (((x) > 0 ? (x) : -(x)) < eps)
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
int e[110], s[110], ans[110];
double d[110][110], dp[110][110];
int main() {
  freopen("C-small-attempt0 (1).in", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, cas = 1, n, q;
  cin >> t;
  while (t--) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
      cin >> e[i] >> s[i];
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        cin >> d[i][j];
        if (d[i][j] == -1)
          d[i][j] = 1e18;
      }
    for (int k = 1; k <= n; ++k)
      for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
          if (d[i][k] + d[k][j] < d[i][j])
            d[i][j] = d[i][k] + d[k][j];
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        if (d[i][j] <= e[i])
          dp[i][j] = 1.0 * d[i][j] / s[i];
        else
          dp[i][j] = 1e18;
    for (int k = 1; k <= n; ++k)
      for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
          if (dp[i][k] + dp[k][j] < dp[i][j])
            dp[i][j] = dp[i][k] + dp[k][j];
    printf("Case #%d:", cas++);
    while (q--) {
      int l, r;
      cin >> l >> r;
      printf(" %.6f", dp[l][r]);
    }
    puts("");
  }
  return 0;
}
