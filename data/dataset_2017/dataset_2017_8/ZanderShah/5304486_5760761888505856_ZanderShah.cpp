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

int T, R, C;
string grid[30], cgrid[30];
bool flip;

char color(int i, int j, int di, int dj) {
	if (R <= i || i < 0 || C <= j || j < 0) {
		return '?';
	}
	if (grid[i][j] != '?') {
		return grid[i][j];
	}
	return grid[i][j] = color(i + di, j + dj, di, dj);
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> R >> C;
		flip = 0;
		for (int i = 0; i < R; i++) {
			cin >> grid[i];
			// cgrid[i] = grid[i];
		}
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (grid[i][j] == '?') {
					color(i, j, -1, 0);
					if (grid[i][j] == '?') {
						color(i, j, 1, 0);
					}
				}
			}
		}

		for (int j = 0; j < C; j++) {
			for (int i = 0; i < R; i++) {
				if (grid[i][j] == '?') {
					color(i, j, 0, -1);
					if (grid[i][j] == '?') {
						color(i, j, 0, 1);
					}
				}
			}
		}

		cout << "Case #" << t << ":" << endl;
		for (int i = 0; i < R; i++) {
			cout << grid[i] << endl;
		}
	}
}
