#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdio>

//#include <cstdint>
//#include <cstdlib>
#include <cassert>
//#include <cctype>
#include <climits>
#include <functional>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <ctime>

#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <list>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <array>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define forn1(i, n) for(int i = 1; i <= int(n); i++)
#define sz(a) int((a).size())
#define all(a) (a).begin(), (a).end()
#define mp make_pair
#define pb push_back
#define x first
#define y second

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld PI = acosl(ld(-1));
const ld EPS = 1e-9;

template <typename T> inline T sqr(const T& x) {
	return x * x;
}

template <typename T> inline T abs(const T& x) {
	return x > 0 ? x : -x;
}

inline bool inside(int x, int y, int n, int m) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}

inline int rnd() {
	return abs(rand() ^ (rand() << 15));
}

inline int rnd(int n) {
	assert(n > 0);
	return rnd() % n;
}

inline int rnd(int lf, int rg) {
	return lf + rnd(rg - lf + 1);
}

inline li rndLL() {
	return rnd() * 1LL * rnd() + rnd();
}

const int dx[4] = { -1, 0, +1, 0 };
const int dy[4] = { 0, +1, 0, -1 };

const int dx8[8] = { -1, -1, 0, +1, +1, +1, 0, -1 };
const int dy8[8] = { 0, +1, +1, +1, 0, -1, -1, -1 };

const int N = int(33);

int n, m, a[N], b[N][N];

inline void gen() {
	return;
}

inline bool read() {
	if (!(cin >> n >> m)) return false;
	forn(i, n) (cin >> a[i]);
	forn(i, n) {
		forn(j, m) (cin >> b[i][j]);
	}
	return true;
}

bool used[N][N];
int ans = 0;

inline bool can(const vector<int>& v) {
	//cerr << "v to check == " << endl;
	//for (int x : v) cerr << x << ' '; cerr << endl;
	for (int cnt = 1; cnt <= 1111111; cnt++) {
		bool ok = true;
		//cerr << "cnt == " << cnt << endl;
		forn(i, n) {
		//	cerr << "ing == " << i << endl;
			li need = a[i] * 1LL * cnt;
			li lf = need * 90;
			if (lf % 100 == 0) lf /= 100;
			else lf = lf / 100 + 1;
			li rg = need * 110;
			rg /= 100;
			li cur = v[i];
			//cerr << "lf rg cur == " << lf << ' ' << rg << ' ' << cur << endl;
			if (!(lf <= cur && cur <= rg)) {
				ok = false;
				//break;
			}
		}

		if (ok) return true;
		//if (cnt > 5) break;
	}

	//cerr << "wtf == " << endl;
	return false;
}

void brute(int cnt, int i, int cur, vector<int> v) {
	//cerr << "cnt i cur == " << cnt << ' ' << i << ' ' << cur << endl;
	if (cnt == m) {
		ans = max(ans, cur);
		return;
	}

	if (i == n) {
		cur += can(v);
		brute(cnt + 1, 0, cur, {});
		return;
	}

	forn(j, m) if (!used[i][j]) {
		used[i][j] = true;
		v.push_back(b[i][j]);
		brute(cnt, i + 1, cur, v);
		v.pop_back(); 
		used[i][j] = false;
	}
}

bool good[N][N];

inline void solve() {
	forn(i, N) forn(j, N) good[i][j] = used[i][j] = false;
	ans = 0;
	//brute(0, 0, 0, {});
	if (n == 1) {
		forn(j, m) ans += can(vector<int>(1, b[0][j]));
	}
	else if(n == 2) {
		forn(i, m) forn(j, m) good[i][j] = can({ b[0][i], b[1][j] });
		vector<vector<int> > dp((1 << m), vector<int>((1 << m), -1));
		dp[0][0] = 0;
		forn(mask1, (1 << m)) forn(mask2, (1 << m)) {
			int cur = dp[mask1][mask2];
			if (cur < 0) continue;
			forn(i, m) {
				if (mask1 & (1 << i)) continue;
				forn(j, m) {
					if (mask2 & (1 << j)) continue;
					dp[mask1 | (1 << i)][mask2 | (1 << j)] = max(dp[mask1 | (1 << i)][mask2 | (1 << j)], cur + good[i][j]);
				}
			}
		}

		forn(mask1, (1 << m)) forn(mask2, (1 << m)) ans = max(ans, dp[mask1][mask2]);
	}
	else cerr << "bad test" << endl;
	cout << ans << endl;
	return;
}

int main() {
	//assert(false);
//#ifdef _DEBUG
	(freopen("input.txt", "rt", stdin));
	(freopen("output.txt", "wt", stdout));
//#endif

	cout << setprecision(10) << fixed;
	cerr << setprecision(10) << fixed;

	srand(int(time(NULL)));

	int T = 1;
#define MULTITEST
#ifdef MULTITEST
	(scanf("%d", &T) == 1);
#endif

	forn(i, T) {
//#ifdef _DEBUG
		cerr << "TEST == " << i << endl;
//#endif
		(read());
		//read();
		cout << "Case #" << i + 1 << ": ";
		solve();
		//cerr << "curTime == " << clock() << " ms" << endl;
	}

#ifdef _DEBUG
	cerr << "TIME == " << clock() << " ms" << endl;
#endif
	return 0;
}