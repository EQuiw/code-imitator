#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dp[110][110][110][110]; // <Hd, Ad, Hk, Ak>
const int INF = 1 << 25;

struct S {
	int hd, ad, hk, ak, cnt;
};

void solve() {
	int Hd, Ad, Hk, Ak, B, D;
	cin >> Hd >> Ad >> Hk >> Ak >> B >> D;
	fill((int*)begin(dp), (int*)end(dp), INF);
	dp[Hd][Ad][Hk][Ak] = 0;

	queue<S> q;
	q.push({ Hd, Ad, Hk, Ak, 0 });

	while(q.size()) {
		S s = q.front();
		q.pop();
		int cnt = s.cnt;
		int hd = s.hd, ad = s.ad, hk = s.hk, ak = s.ak;
		if(hk - ad <= 0) {
			cout << cnt + 1 << endl;
			return;
		}
		if(hd - ak > 0) {
			if(dp[hd - ak][ad][hk - ad][ak] > cnt + 1) {
				dp[hd - ak][ad][hk - ad][ak] = cnt + 1;
				q.push({ hd - ak, ad, hk - ad, ak, cnt + 1 });
			}
			if(dp[hd - ak][min(ad + B, 100)][hk][ak] > cnt + 1) {
				dp[hd - ak][min(ad + B, 100)][hk][ak] = cnt + 1;
				q.push({ hd - ak, min(ad + B, 100), hk, ak, cnt + 1 });
			}

		}


		if(Hd - ak > 0) {
			if(dp[Hd - ak][ad][hk][ak] > cnt + 1) {
				dp[Hd - ak][ad][hk][ak] = cnt + 1;
				q.push({ Hd - ak, ad, hk, ak, cnt + 1 });
			}
		}

		ak = max(ak - D, 0);
		if(hd - ak > 0) {
			if(dp[hd - ak][ad][hk][ak] > cnt + 1) {
				dp[hd - ak][ad][hk][ak] = cnt + 1;
				q.push({ hd - ak, ad, hk, ak , cnt + 1 });
			}
		}
	}

	cout << "IMPOSSIBLE" << endl;
}


int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	for(int i = 0; i < T; i++) {
		cout << "Case #" << i + 1 << ": ";
		solve();
	}
}