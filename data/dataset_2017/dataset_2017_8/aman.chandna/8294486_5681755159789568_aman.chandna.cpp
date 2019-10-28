#define boost ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define mod 1000000007
#define INF LLONG_MAX
#include <unordered_set>
#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll double
#define lpair pair<double,double>
int main() {

	boost;
	freopen("inp3.txt", "r", stdin);
	freopen("out3.txt", "w", stdout);
	long long t;
	cin >> t;
	cout << std::fixed;
	for (long long ccr = 1; ccr <= t; ++ccr) {
		ll n, q;
		cin >> n >> q;
		lpair in;
		vector<lpair> hinfo(n, in);
		for (ll i = 0; i < n; ++i)
			cin >> hinfo[i].first >> hinfo[i].second;
		vector<vector<ll> > graph(n, vector<ll>(n, 0));
		for (ll i = 0; i < n; ++i) {
			for (ll j = 0; j < n; ++j) {
				cin >> graph[i][j];
			}
		}
		vector<ll> ans(n, 0.0);
		for (ll i = n - 2; i >= 0; --i) {
			ll opt = DBL_MAX;
			ll dist = 0.0;
			for (ll j = i + 1; j < n; ++j) {
				dist += graph[j - 1][j];
				if (dist <= hinfo[i].first) {
					opt = min(opt, dist / hinfo[i].second + ans[j]);
				}
				else {
					break;
				}
			}
			ans[i] = opt;
		}
		for (ll i = 0; i < q; ++i) {
			ll aa;
			cin >> aa >> aa;
		}
		cout << "Case #" << ccr << ": " <<setprecision(7)<< ans[0] << "\n";\

	}
	return 0;
}