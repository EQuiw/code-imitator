#define boost ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define mod 1000000007
#define INF LLONG_MAX
#include <unordered_set>
#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll long long

//struct my {
//	ll start,end;
//	bool iscam;
//};

int main() {

	boost;
	freopen("inp2.txt", "r", stdin);
	freopen("out2.txt", "w", stdout);
	ll t;
	cin >> t;
	for (ll ccr = 1; ccr <= t; ++ccr) {
		ll ans = 0;
		ll ac, aj;
		cin >> ac >> aj;
		vector<pair<ll, ll> > c(ac, {0.0,0.0}), j(aj, { 0.0,0.0 });
		
		for (ll i = 0; i < ac; ++i)
			cin >> c[i].first >> c[i].second;
		for (ll i = 0; i < aj; ++i)
			cin >> j[i].first >> j[i].second;
		sort(j.begin(), j.end());
		sort(c.begin(), c.end());
		if (aj == 0 && ac == 1 || aj == 1 && ac == 0)
			ans = 2;
		else if (ac == 0) {
			ans = 4;
			if (j[1].second - j[0].first <= 720) {
				ans = 2;
			}
			ll val = 1440 - j[1].first + j[0].second;
			if (val<=720) {
				ans = 2;
			}
		}
		else if (aj == 0 && ac == 2) {
			ans = 4;
			if (c[1].second - c[0].first <= 720) {
				ans = 2;
			}
			ll val = 1440 - c[1].first + c[0].second;
			if (val <= 720) {
				ans = 2;
			}
		}
		else {
			ans = 2;
		}
		cout << "Case #" << ccr << ": " << ans << "\n";
	}

	return 0;
}