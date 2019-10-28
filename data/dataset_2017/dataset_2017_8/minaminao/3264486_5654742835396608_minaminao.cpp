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
	freopen("C-small-1-attempt0.in", "r", stdin);
	freopen("C-small-1-attempt0.txt", "w", stdout);
	int T; cin >> T;
	for (int t = 0; t < T; t++) {
		int N; cin >> N;
		int K; cin >> K;
		priority_queue<int> pq;
		pq.emplace(N);
		rep(k, 0, K) {
			int a = pq.top(); pq.pop();
			a--;
			int b = a / 2, c = a - b;
			//dump(a, b, c);
			pq.emplace(b);
			pq.emplace(c);
			if (k == K - 1) {
				cout << "Case #" << t + 1 << ": ";
				cout << max(b, c) << " " << min(b, c) << endl;
			}
		}
	}
	return 0;
}