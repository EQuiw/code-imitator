#include "bits/stdc++.h"
using namespace std;
#ifdef _DEBUG
#include "dump.hpp"
#else
#define dump(...)
#endif

//#define int long long
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
	freopen("A-small-attempt0.in", "r", stdin);
	freopen("A-small-attempt0.txt", "w", stdout);
	int T; cin >> T;
	for (int t = 0; t < T; t++) {
		string S; cin >> S;
		int n = S.size();
		vector<bool> v(n);
		rep(i, 0, n)v[i] = S[i] == '+';
		int K; cin >> K;
		int ans = 0;
		rep(i, 0, n) {
			if (i + K > n)break;
			if (v[i])continue;
			ans++;
			rep(j, i, i + K) {
				v[j] = !v[j];
			}
			//dump(v);
		}
		bool flag = true;
		rep(i, 0, n)
			if (!v[i])
				flag = false;
		cout << "Case #" << t + 1 << ": ";
		if (flag) {
			cout << ans << endl;
		}
		else {
			cout << "IMPOSSIBLE" << endl;
		}
	}
	return 0;
}