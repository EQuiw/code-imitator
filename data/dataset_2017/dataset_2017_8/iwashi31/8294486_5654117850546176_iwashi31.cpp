#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <list>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#define int long long
#define MOD7 1000000007
#define MOD9 1000000009

#define rep(i, n) for (int i = 0; i < (n); i++)
#define REP(i, a, n) for (int i = (a); i <= (n); i++)
#define all(a) (a).begin(), (a).end()

using namespace std;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, -1, 0, 1 };

int nextInt() {int a; cin >> a; return a;}
char nextChar() {char a; cin >> a; return a;}
double nextDouble() {double a; cin >> a; return a;}
string nextString() {string a; cin >> a; return a;}

template<class T> void inputVector(vector<T>& v, int n) {
    v.resize(n);
    for (int i = 0; i < v.size(); i++) cin >> v[i];
}

signed main() {
	int T;
	cin >> T;

	REP(loop, 1, T) {
		int N, R, O, Y, G, B, V;
		cin >> N >> R >> O >> Y >> G >> B >> V;

		string ret = string(N, '.');
		if (2 * R > N
			|| 2 * Y > N
			|| 2 * B > N) ret = "IMPOSSIBLE";
		else {
			int pt = 0;
			rep(j, 3) {
				if (R + Y + B == 0) break;
				if (R >= Y && R >= B) {
					rep(i, R) {
						ret[pt] = 'R';
						pt += 2;
						if (pt >= N) pt = 1;
					}
					R = 0;
				} else if (Y >= R && Y >= B) {
					rep(i, Y) {
						ret[pt] = 'Y';
						pt += 2;
						if (pt >= N) pt = 1;
					}
					Y = 0;
				} else if (B >= R && B >= Y) {
					rep(i, B) {
						ret[pt] = 'B';
						pt += 2;
						if (pt >= N) pt = 1;
					}
					B = 0;
				}
			}
		}

		cout << "Case #" << loop << ": " << ret << endl;
	}

    return 0;
}
