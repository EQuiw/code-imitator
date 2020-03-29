#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, P;
int g[100];
int dp[4][101][101][101];

int f(int t, int r1, int r2, int r3) {
	int& d = dp[t][r1][r2][r3];
	if(d != -1) return d;

	if(r1 + r2 + r3 == 0) {
		return 0;
	}

	d = 0;
	if(r1) {
		d = max(d, f((t - 1 + P) % P, r1 - 1, r2, r3) + (t == 0));
	}
	if(r2) {
		d = max(d, f((t - 2 + P) % P, r1, r2 - 1, r3) + (t == 0));
	}
	if(r3) {
		d = max(d, f((t - 3 + P) % P, r1, r2, r3 - 1) + (t == 0));
	}
	return d;
}

void solve() {
	cin >> N >> P;

	int c[4] = { 0 };
	for(int i = 0; i < N; i++) {
		cin >> g[i];
		c[g[i] % P]++;
	}
	memset(dp, -1, sizeof dp);
	int ans = f(0, c[1], c[2], c[3]) + c[0];
	cout << ans << endl;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	for(int i = 0; i < T; i++) {
		cerr << i << endl;
		cout << "Case #" << i + 1 << ": ";
		solve();
	}
}