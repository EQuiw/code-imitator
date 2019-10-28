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
	ifstream ifs("c.in");
	ofstream ofs("c.out");
	
	int t;
	ifs >> t;
	for (int test = 0; test < t; ++test) {
		long long n, k;
		ifs >> n >> k;
		map<long long, long long> m;
		m[n] = 1;
		long long cnt = 0, mx, mn;
		while (!m.empty()) {
			long long len, c;
			tie(len, c) = *m.rbegin();
			m.erase(len);
			mx = len / 2;
			mn = len - mx - 1;
			cnt += c;
			if (cnt >= k) {
				break;
			}
			if (mx > 0)
				m[mx] += c;
			if (mn > 0)
				m[mn] += c;
		}
		ofs << "Case #" << test + 1 << ": " << mx << ' ' << mn << endl;
	}
	return 0;
}
