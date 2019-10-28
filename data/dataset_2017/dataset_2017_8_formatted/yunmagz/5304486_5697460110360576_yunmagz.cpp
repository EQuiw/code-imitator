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
int a[55], q[55][55], v[55], vis[55][55], ans, n, p;
void solve() {
  memset(vis, 0, sizeof vis);
  int g = 1, f = 1;
  while (f) {
    int cnt = 0;
    memset(v, 0, sizeof v);
    for (int i = 0; i < n; i++) {
      double l = a[i] * g * 0.9, r = a[i] * g * 1.1;
      for (int j = 0; j < p; j++) {
        if (vis[i][j])
          continue;
        if (q[i][j] >= l && q[i][j] <= r) {
          cnt++;
          v[i] = j;
          break;
        }
      }
      if (q[i][p - 1] < l)
        f = 0;
    }
    if (cnt == n) {
      ans++;
      for (int i = 0; i < n; i++)
        vis[i][v[i]] = 1;
    } else
      g++;
  }
}
int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, cas = 1;
  cin >> t;
  while (t--) {
    cin >> n >> p;
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++)
        cin >> q[i][j];
      sort(q[i], q[i] + p);
    }
    ans = 0;
    solve();

    printf("Case #%d: %d\n", cas++, ans);
  }
  return 0;
}
