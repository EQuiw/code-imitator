#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
#include <deque>
#include <unordered_map>
#include <map>
#include <bitset>
#include <string>
#include <cstring>

#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define scan(x) do {while((x=getchar())<'0') ; for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0') ; } while(0)
char _;
#define x first
#define y second

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef map<int, int> mii;
typedef unordered_map<int, int> umii;

int T, N, K, x[1005], c, f, ii, l, r, y[1005];

int left(int i) {
	while (x[i] == 0) {
		i--;
	}
	return i;
}

int right(int i) {
	while (x[i] == 0) {
		i++;
	}
	return i;
}

int main() {
	scanf("%d", &T);
	for (int rr = 1; rr <= T; rr++) {

		scanf("%d %d", &N, &K);
		memset(x, 0, sizeof x);
		x[0] = x[N + 1] = -1;

		for (int i = 1; i <= K; i++) {
			c = -1;
			f = -1;
			ii = -1;

			for (int j = 1; j <= N; j++) {
				if (x[j]) {
					continue;
				}
				l = j - left(j - 1) - 1;
				r = right(j + 1) - j - 1;
				if (c < min(l, r) || (c == min(l, r) && f < max(l, r))) {
					c = min(l, r);
					f = max(l, r);
					ii = j;
				}
			}

			x[ii] = i;
			y[i] = ii;
		}

		cout << "Case #" << rr << ": " << f << " " << c << endl;
	}
}
