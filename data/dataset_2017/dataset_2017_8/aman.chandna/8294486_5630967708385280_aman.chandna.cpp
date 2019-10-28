#define boost ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define mod 1000000007
#define INF LLONG_MAX
#include <unordered_set>
#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll double


int main() {

	boost;
	freopen("inp1.txt", "r", stdin);
	freopen("out1.txt", "w", stdout);
	ll t;
	cin >> t;
	cout << std::fixed;
	for (long long ccr = 1; ccr <= t; ++ccr) {
		ll d, n,ans=INT_MIN;
		cin >> d >> n;
		for (ll i = 0; i < n; ++i) {
			ll k, s;
			cin >> k >> s;
			k = d - k;
			ll tme= k / s;
			ans = max(ans, tme);
		}
		ans = d / ans;
	cout << "Case #" << ccr << ": " <<setprecision(7) <<ans << "\n";
		

			
			
	}
	
	return 0;
}