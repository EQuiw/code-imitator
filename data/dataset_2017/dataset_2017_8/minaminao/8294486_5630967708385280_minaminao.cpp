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

template<class T, class ...Tail>
void tied_sort(vector<T> &a, vector<Tail>&... tail) {
	int n = a.size();
	using S = tuple<T, Tail...>;
	vector<S> s(n);
	for (int i = 0; i < n; i++)
		s[i] = make_tuple(a[i], tail[i]...);
	sort(s.begin(), s.end());
	for (int i = 0; i < n; i++)
		tie(a[i], tail[i]...) = s[i];
}

signed main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	freopen("A-small-attempt1.in", "r", stdin);
	freopen("A-small-attempt1.txt", "w", stdout);
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int T; cin >> T;
	cout << fixed << setprecision(10);
	for (int t = 0; t < T; t++) {
		double D; int N; cin >> D >> N;
		if (N > 2)break;
		vector<double> K(N), S(N); rep(i, 0, N) {
			cin >> K[i] >> S[i];
		}
		tied_sort(K, S);
		dump(K, S);
		double totaltime = 0;
		rep(i, 0, N - 1) {
			double mint = INF;
			int minid = -1;
			rep(j, 0, N - 1) {
				if (K[j] > D)break;
				if (S[i + 1] > S[i])continue;
				double time = (K[i + 1] - K[i]) / (S[i] - S[i + 1]);
				if (K[j] + S[j] * time > D)continue;
				if (chmin(mint, time)) {
					minid = j;
				}
			}
			if (minid == -1) {
				break;
			}
			rep(j, 0, N) {
				K[j] += S[j] * mint;
			}
			S[minid] = S[minid + 1];
			totaltime += mint;
		}
		double ans = 0;
		totaltime += (D - K[0]) / S[0];
		ans += D / totaltime;
		cout << "Case #" << t + 1 << ": " << ans << endl;
	}
	return 0;
}