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
		double res = 0;
		int d, n;
		ifs >> d >> n;
		double maxt = 0;
		for (int i = 0; i < n; ++i) {
			int k, s;
			ifs >> k >> s;

			maxt = max(maxt, (d - k) / (double)s);
		}
		ofs << "Case #" << test + 1 << ": " << setprecision(10) << fixed << d / maxt << endl;
	}
	return 0;
}
