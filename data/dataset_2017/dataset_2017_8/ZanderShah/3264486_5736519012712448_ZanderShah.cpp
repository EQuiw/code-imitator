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

int T, w, m;
string s;

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	cin >> T;
	for (int r = 1; r <= T; r++) {
		cin >> s >> w;
		m = 0;

		for (int i = 0; i < s.length() - w + 1; i++) {
			if (s[i] == '-') {
				for (int j = 0; j < w; j++) {
					s[i + j] = s[i + j] == '+' ? '-' : '+';
				}
				m++;
			}
		}

		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '-') {
				m = -1;
			}
		}

		cout << "Case #" << r << ": ";
		if (m == -1) {
			cout << "IMPOSSIBLE" << endl;
		} else {
			cout << m << endl;
		}
	}
}
