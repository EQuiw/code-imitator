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
		string s; int k;
		ifs >> s >> k;

		int res = 0;
		for (int i = 0; i < s.length() - k + 1; ++i) {
			if (s[i] == '-') {
				for (int j = 0; j < k; ++j) {
					if (s[i+j] == '-') s[i+j] = '+'; else s[i+j] = '-';
				}
				++res;
			}
		}

		bool ok = s.find('-') == -1;
		ofs << "Case #" << test + 1 << ": " << (ok ? to_string(res) : "IMPOSSIBLE") << endl;
	}
	return 0;
}
