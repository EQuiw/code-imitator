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

void flip(string &s, int x, int k) {
	for (int i = x; i < x + k; i++)
		s[i] = (s[i] == '+' ? '-' : '+');
}

int main () {
	ios::sync_with_stdio(false);

	int tt; cin >> tt;
	for (int tc = 1; tc <= tt; tc++) {
		cout << "Case #" << tc << ": ";

		string s; cin >> s;
		int k; cin >> k;

		int n = SZ(s);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == '-') {
				if (n - i >= k) {
					flip(s, i, k);
					ans++;
				} else {
					ans = -1;
					break;
				}
			}
		}
		if (ans == -1) cout << "IMPOSSIBLE";
		else cout << ans;
		cout << endl;
	}
	return 0;
}

