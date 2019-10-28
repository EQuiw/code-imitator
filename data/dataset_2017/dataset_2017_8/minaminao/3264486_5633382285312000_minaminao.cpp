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
	int T; cin >> T;
	for (int t = 0; t < T; t++) {

		int N; cin >> N;
		string s = to_string(N);
		int n = s.size();
		vector<int> pow10(n);
		pow10[0] = 1;
		rep(i, 0, n - 1)pow10[i + 1] = pow10[i] * 10;
		dump(pow10);
		while (true) {
			int m = 0;
			rep(i, 1, n) {
				if (s[i - 1] <= s[i])m++;
				else break;
			}
			dump(m);
			if (m == n - 1)break;
			N -= N%pow10[n - 1 - m];
			N--;
			dump(N);
			s = to_string(N);
			n = s.size();
		}
		cout << "Case #" << t + 1 << ": ";
		cout << N << endl;


		//bool flag = true;
		//rep(i, 0, n)
		//	if (!v[i])
		//		flag = false;
		//cout << "Case #" << t + 1 << ": ";
		//if (flag) {
		//	cout << ans << endl;
		//}
		//else {
		//	cout << "IMPOSSIBLE" << endl;
		//}
	}
	return 0;
}