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

const int MAXN = 1 * 100 + 10;

int r[MAXN];
int q[MAXN][MAXN];
set<pair<pii, int> > s[MAXN];

int main () {
	ios::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
		FOR(i, MAXN) s[i].clear();
		cout << "Case #" << tt << ": ";

		int n, p; cin >> n >> p;
		for (int i = 0; i < n; i++)
			cin >> r[i];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < p; j++)
				cin >> q[i][j];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < p; j++)	{
				int k1 = ceil((double)q[i][j] / ((double)r[i] * 1.1));
				int k2 = floor((double)q[i][j] / ((double)r[i] * 0.9));

				if (k1 <= k2) s[i].insert(mp(mp(k1, k2), j));
			}

		int ans = 0;
		while (SZ(s[0])) {
			pair<pii, int> tmp = *s[0].begin();
			s[0].erase(s[0].begin());
			int k1 = tmp.X.X, k2 = tmp.X.Y;

			bool check = true;
			for (int i = 1; i < n; i++) {
				if (s[i].empty()) check = false;
				
				while (SZ(s[i])) {
					pair<pii, int> tmp = *s[i].begin();
					int t1 = tmp.X.X, t2 = tmp.X.Y;
					if (t2 < k1) {
						s[i].erase(s[i].begin());
						if (s[i].empty()) check = false;
						continue;
					}
					k1 = max(k1, t1);
					k2 = min(k2, t2);
					break;
				}
			}
			if (k1 <= k2 && check) {
				for (int i = 1; i < n;i ++)
					s[i].erase(s[i].begin());
				ans++;
			}
		}
		cout << ans << endl;
	}
	return 0;
}

