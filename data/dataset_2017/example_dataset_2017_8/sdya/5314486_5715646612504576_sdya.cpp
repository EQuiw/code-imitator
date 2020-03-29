#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <cmath>
#include <ctime>
#pragma comment (linker, "/STACK:256000000")

using namespace std;

void readData() {
}

const int maxN = 8;
const int maxM = 60;
string s[maxN];
int n, m;

string c[maxN];
int used[maxN][maxM];

bool check2() {
	memset(used, 0, sizeof(used));
	for (int x = 0; x < n; ++x) {
		for (int y = 0; y < m; ++y) {
			if (s[x][y] == '-' || s[x][y] == '|') {
				for (int i = y - 1; i >= 0; --i) {
					if (s[x][i] != '.') {
						break;
					}
					used[x][i] = true;
				}
				for (int i = y + 1; i < m; ++i) {
					if (s[x][i] != '.') {
						break;
					}
					used[x][i] = true;
				}
			}
			if (s[x][y] == '|' || s[x][y] == '-') {
				for (int i = x - 1; i >= 0; --i) {
					if (s[i][y] != '.') {
						break;
					}
					used[i][y] = true;
				}
				for (int i = x + 1; i < n; ++i) {
					if (s[i][y] != '.') {
						break;
					}
					used[i][y] = true;
				}
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == '.' && !used[i][j]) {
				return false;
			}
		}
	}
	return true;
}

bool check() {
	memset(used, 0, sizeof(used));
	for (int x = 0; x < n; ++x) {
		for (int y = 0; y < m; ++y) {
			if (s[x][y] == '-') {
				for (int i = y - 1; i >= 0; --i) {
					if (s[x][i] != '.') {
						break;
					}
					used[x][i] = true;
				}
				for (int i = y + 1; i < m; ++i) {
					if (s[x][i] != '.') {
						break;
					}
					used[x][i] = true;
				}
			}
			if (s[x][y] == '|') {
				for (int i = x - 1; i >= 0; --i) {
					if (s[i][y] != '.') {
						break;
					}
					used[i][y] = true;
				}
				for (int i = x + 1; i < n; ++i) {
					if (s[i][y] != '.') {
						break;
					}
					used[i][y] = true;
				}
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == '.' && !used[i][j]) {
				return false;
			}
		}
	}
	return true;
}

bool rec(int x, int y) {
	if (y == m) {
		return check();
	}

	if (x == n) {
		return rec(0, y + 1);
	}

	if (s[x][y] != '-' && s[x][y] != '|') {
		return rec(x + 1, y);
	}

	bool a = true;
	bool b = true;
	{
		for (int i = y - 1; i >= 0; --i) {
			if (s[x][i] == '#') {
				break;
			}
			if (s[x][i] == '|' || s[x][i] == '-') {
				a = false;
			}
		}
		for (int i = y + 1; i < m; ++i) {
			if (s[x][i] == '#') {
				break;
			}
			if (s[x][i] == '|' || s[x][i] == '-') {
				a = false;
			}
		}
	}

	{
		for (int i = x - 1; i >= 0; --i) {
			if (s[i][y] == '#') {
				break;
			}
			if (s[i][y] == '|' || s[i][y] == '-') {
				b = false;
			}
		}
		for (int i = x + 1; i < n; ++i) {
			if (s[i][y] == '#') {
				break;
			}
			if (s[i][y] == '|' || s[i][y] == '-') {
				b = false;
			}
		}
	}
	if (a) {
		s[x][y] = '-';
		if (rec(x + 1, y)) {
			return true;
		}
	}
	if (b) {
		s[x][y] = '|';
		if (rec(x + 1, y)) {
			return true;
		}
	}
	return false;
 }

void solve(int test) {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> s[i];
	}
	if (check2() && rec(0, 0)) {
		printf("Case #%d: POSSIBLE\n", test);
		for (int i = 0; i < n; ++i) {
			cout << s[i] << endl;
		}
	} else {
		printf("Case #%d: IMPOSSIBLE\n", test);
	}
}

int main(int argc, char* argv[]) {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int left_bound, right_bound;

	/*freopen(argv[3], "w", stdout);	
	sscanf(argv[1], "%d", &left_bound);
	sscanf(argv[2], "%d", &right_bound);*/

	int t;
	cin >> t;
	left_bound = 1, right_bound = t;
	for (int i = 1; i <= t; ++i) {
		if (i >= left_bound && i <= right_bound) {
			solve(i);
		}
		cerr << i << ": " << clock() << endl;
	}

	return 0;
}
