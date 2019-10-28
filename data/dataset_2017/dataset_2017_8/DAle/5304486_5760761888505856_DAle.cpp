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

int main() {
	ios_base::sync_with_stdio(false);
	ifstream ifs("a.in");
	ofstream ofs("a.out");
	
	int t;
	ifs >> t;
	for (int test = 0; test < t; ++test) {
		int res = 0;
		int n, m;
		ifs >> n >> m;
		vector<string> v(n);

		for (int i = 0; i < n; ++i)
			ifs >> v[i];

		bool found = false;
		int sx;
		for (int i = 0; i < n && !found; ++i)
			for (int j = 0; j < m; ++j)
				if (v[i][j] != '?') {
					sx = i;
					found = true;
					break;
				}

		for (int i = sx; i < n; ++i) {
			char f = '?';
			for (int j = 0; j < m; ++j)
				if (v[i][j] != '?') {
					f = v[i][j];
					break;
				}
			if (f != '?') {
				for (int j = 0; j < m; ++j) {
					if (v[i][j] == '?' || v[i][j] == f) {
						v[i][j] = f;
					}
					else {
						f = v[i][j];
					}
				}
			}
			else {
				v[i] = v[i - 1];
			}
		}

		for (int i = 0; i < sx; ++i)
			v[i] = v[sx];
		ofs << "Case #" << test + 1 << ":" << endl;
		for (auto s : v) {
			ofs << s << endl;
		}
	}
	return 0;
}
