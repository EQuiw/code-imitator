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

pair<int, char> p[10];

int main () {
	ios::sync_with_stdio(false);

	int tt; cin >> tt;
	for (int tc = 1; tc <= tt; tc++) {
		cout << "Case #" << tc << ": ";

		int n, r, o, y, g, b, v;
		cin >> n >> r >> o >> y >> g >> b >> v;

		p[0] = mp(r, 'R');
		p[1] = mp(y, 'Y');
		p[2] = mp(b, 'B');
		sort(p, p + 3);

		if (p[2].X > n / 2) {
			cout << "IMPOSSIBLE" << endl;
		}
		else {
			string ans;
			for (int i = 0; i < n; i++) ans.pb(' ');

			for (int c = 2; c >= 0; c--) {
				if (c % 2 == 0) {
					for (int i = 0; i < n; i++) {
						if (p[c].X == 0) break;

						int prev = (i - 1 + n) % n;
						if (ans[prev] != p[c].Y && ans[i] == ' ') {
							ans[i] = p[c].Y;
							p[c].X--;
						}
					}
				} else {
					for (int i = n-1; i >= 0; i--) {
						if (p[c].X == 0) break;

						int next = (i + 1 + n) % n;
						if (ans[next] != p[c].Y && ans[i] == ' ') {
							ans[i] = p[c].Y;
							p[c].X--;
						}
					}
				}
			}
			for (int i = 0; i < n; i++)
				if (ans[i] == ' ')
					cerr << "BUG" << endl;

			cout << ans << endl;
		}
	}
	return 0;
}

