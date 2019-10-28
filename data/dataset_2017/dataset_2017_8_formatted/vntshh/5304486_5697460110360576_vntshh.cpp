#include <bits/stdc++.h>
#define rep(i, start, lim) for (lld i = start; i < lim; i++)
#define repd(i, start, lim) for (lld i = start; i >= lim; i--)
#define scan(x) scanf("%lld", &x)
#define print(x) printf("%lld ", x)
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define br printf("\n")
#define YES printf("YES\n")
#define NO printf("NO\n")
#define all(c) (c).begin(), (c).end()
using namespace std;
#define INF 1011111111
#define LLINF 1000111000111000111LL
#define EPS (double)1e-10
#define MOD 1000000007
#define PI 3.14159265358979323
using namespace std;
typedef long double ldb;
typedef long long lld;
lld powm(lld base, lld exp, lld mod = MOD) {
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
#define N 55
const int MAXN = (1 << 16);
lld r[N], q[N][N], dp[MAXN];
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
  rep(tt, 1, t + 1) {
    cin >> n >> p;
    rep(i, 0, n) cin >> r[i];
    rep(i, 0, n) rep(j, 0, p) cin >> q[i][j];
    rep(i, 0, MAXN) dp[i] = 0;
    cout << "Case #" << tt << ": ";
    if (n == 1) {
      lld cnt = 0;
      rep(i, 0, p) {
        ldb a1 = floor((ldb)(10 * q[0][i]) / (9 * r[0]));
        ldb a2 = ceil((ldb)(10 * q[0][i]) / (11 * r[0]));
        cnt += (lld)(a2 <= a1);
      }
      cout << cnt << endl;
    } else if (n == 2) {
      lld mask = (1 << (2 * p));
      rep(i, 0, mask) {
        rep(j, 0, p) rep(k, p, 2 * p) {
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