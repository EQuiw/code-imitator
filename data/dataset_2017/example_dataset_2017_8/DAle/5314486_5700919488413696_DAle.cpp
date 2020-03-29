#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <functional>
#include <utility>
#include <tuple>
#include <numeric>
#include <queue>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <regex>
#include <stack>
#include <limits>

using namespace std;

int f[101][101][101][4];

void clearf(int a, int b, int c) {
	for (int i = 0; i <= a; ++i)
		for (int j = 0; j <= b; ++j)
			for (int k = 0; k <= c; ++k) {
				for (int d = 0; d < 4; ++d)
					f[i][j][k][d] = -1;
			}
}

int count(int a, int b, int c, int d, int p) {
	int& res = f[a][b][c][d];
	if (res != -1) {
		return res;
	}
	if (a == 0 && b == 0 && c == 0) return res = 0;
	int best = 0;
	if (a > 0) {
		int newd = (d + 1) % p;
		int bs = count(a - 1, b, c, newd, p);
		if (newd == 0) ++bs;
		best = max(best, bs);
	}
	if (b > 0) {
		int newd = (d + 2) % p;
		int bs = count(a, b-1, c, newd, p);
		if (newd == 0) ++bs;
		best = max(best, bs);
	}
	if (c > 0) {
		int newd = (d + 3) % p;
		int bs = count(a, b, c - 1, newd, p);
		if (newd == 0) ++bs;
		best = max(best, bs);
	}
	return res = best;
}

int count(const vector<int>& cnt, int p) {
	return cnt[0] + 1 + count(cnt[1], cnt[2], cnt[3], 0, p);
}

int main() {
	ios_base::sync_with_stdio(false);
	ifstream ifs("a.in");
	ofstream ofs("a.out");
	
	int t;
	ifs >> t;
	for (int test = 0; test < t; ++test) {
		int n, p;
		ifs >> n >> p;

		vector<int> cnt(4);
		for (int i = 0; i < n; ++i) {
			int k;
			ifs >> k;
			cnt[k % p]++;
		}
		clearf(cnt[1], cnt[2], cnt[3]);
		int best = 0;
		for (int i = 0; i < 4; ++i) {
			if (cnt[i] > 0) {
				cnt[i]--;
				best = max(best, count(cnt, p));
				cnt[i]++;
			}
		}
		ofs << "Case #" << test + 1 << ": " << best << endl;
	}
	return 0;
}
