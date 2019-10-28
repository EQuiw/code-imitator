#define boost ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define mod 1000000007
#define INF LLONG_MAX
#include <unordered_set>
#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll long long

int main() {

	boost;
	freopen("inp2.txt", "r", stdin);
	freopen("out2.txt", "w", stdout);
	ll t;
	cin >> t;
	for (ll ccr = 1; ccr <= t; ++ccr) {
		ll n, r, o, y, g, b, v;
		cin >> n >> r>> o>> y>> g>> b>> v;
		string ans(n,'a');
		if (r >= b && r >= y) {
			ans[0] = 'R';
			--r;
		}
		else if (b >= r && b >= y) {
			ans[0] = 'B';
			--b;
		}
		else {
			ans[0] = 'Y';
			--y;
		}
		
		for (int i = 1; i < n; ++i) {
			if (ans[i - 1] == 'R') {
				if (b > y||(b==y && ans[0]=='B' && b>0)) {
					ans[i] = 'B';
					--b;
				}
				else {
					if (y <= 0) {
						ans = "IMPOSSIBLE";
						break;
					}
					ans[i] = 'Y';
					--y;
				}
			}
			else if (ans[i - 1] == 'B') {
				if (r > y || (r == y && ans[0] == 'R' && r>0)) {
					ans[i] = 'R';
					--r;
				}
				else {
					if (y <= 0) {
						ans = "IMPOSSIBLE";
						break;
					}
					ans[i] = 'Y';
					--y;
				}
			}
			else {
				if (r > b || (b == r && ans[0] == 'R' && r>0)) {
					ans[i] = 'R';
					--r;
				}
				else {
					if (b <= 0) {
						ans = "IMPOSSIBLE";
						break;
					}
					ans[i] = 'B';
					--b;
				}
			}
		}
		if (ans!="IMPOSSIBLE" && ans[n - 1] == ans[0]) {
			ans = "IMPOSSIBLE";
		}
		cout << "Case #" << ccr << ": " << ans << "\n";
	}

	return 0;
}