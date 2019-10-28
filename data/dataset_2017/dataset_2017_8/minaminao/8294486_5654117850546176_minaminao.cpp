#include "bits/stdc++.h"
using namespace std;
#ifdef _DEBUG
#include "dump.hpp"
#else
#define dump(...)
#endif

#define int long long
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define rrep(i,a,b) for(int i=(b)-1;i>=(a);i--)
#define all(c) begin(c),end(c)
const int INF = sizeof(int) == sizeof(long long) ? 0x3f3f3f3f3f3f3f3fLL : 0x3f3f3f3f;
const int MOD = (int)(1e9) + 7;
template<class T> bool chmax(T &a, const T &b) { if (a < b) { a = b; return true; } return false; }
template<class T> bool chmin(T &a, const T &b) { if (b < a) { a = b; return true; } return false; }

signed main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	freopen("B-small-attempt0.in", "r", stdin);
	freopen("B-small-attempt0.txt", "w", stdout);
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int T; cin >> T;
	cout << fixed << setprecision(10);
	for (int t = 0; t < T; t++) {
		string ans;

		int N; cin >> N;
		int R, O, Y; cin >> R >> O >> Y;
		int G, B, V; cin >> G >> B >> V;

		int maxi = N / 2;
		if (R > maxi || Y > maxi || B > maxi) {
			ans = "IMPOSSIBLE";
		}
		else {
			using P = pair<int, char>;
			vector<P> v;
			v.emplace_back(R, 'R');
			v.emplace_back(Y, 'Y');
			v.emplace_back(B, 'B');
			sort(all(v));
			reverse(all(v));
			vector<string> p;
			rep(i, 0, v[0].first) {
				p.emplace_back(string(1, v[0].second));
			}
			int cur = 0;
			rep(i, 0, v[1].first) {
				p[(cur++) % p.size()] += v[1].second;
			}
			rep(i, 0, v[2].first) {
				p[(cur++) % p.size()] += v[2].second;
			}
			//dump(p);
			rep(i, 0, p.size()) {
				ans += p[i];
			}
		}
		cout << "Case #" << t + 1 << ": " << ans << endl;
	}
	return 0;
}