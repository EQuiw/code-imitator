#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define SQR(a) ((a) * (a))
#define SZ(x) ((int) (x).size())
#define ALL(x) (x).begin(), (x).end()
#define CLR(x, a) memset(x, a, sizeof x)
#define VAL(x) #x << " = " << (x) << "   "
#define FOREACH(i, x) for(__typeof((x).begin()) i = (x).begin(); i != (x).end(); i ++)
#define FOR(i, n) for (int i = 0; i < (n); i ++)
#define X first
#define Y second

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const int MAXN = 1 * 1000 + 10;
const double PI = acos(-1);

ll dp[MAXN][MAXN];
pll c[MAXN];

int main () {
	ios::sync_with_stdio(false);

	int tt; cin >> tt;
	for (int tc = 1; tc <= tt; tc++) {
		cout << "Case #" << tc << ": ";
		CLR(dp, 0);

		int n, k; cin >> n >> k;
		for (int i = 0; i < n; i++) cin >> c[i].X >> c[i].Y;
		sort(c, c + n);

		for (int j = 1; j <= k; j++) {
			ll cur = 0;
			for (int i = 0; i < n; i++) {
				ll base = 2 * c[i].X * c[i].Y;
				dp[i][j] = cur + base;
				cur = max(cur, dp[i][j - 1]);
			}
		}

		ll ans = 0;
		for (int i = 0; i < n; i++)
			ans = max(ans, dp[i][k] + SQR(c[i].X));
		cout << fixed << setprecision(6) << ans * PI << endl;
	}
	return 0;
}

