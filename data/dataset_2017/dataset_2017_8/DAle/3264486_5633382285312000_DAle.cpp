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
	ifstream ifs("b.in");
	ofstream ofs("b.out");
	
	int t;
	ifs >> t;
	for (int test = 0; test < t; ++test) {
		string s;
		ifs >> s;
		int pos = -1;
		for (int i = 1; i < s.size(); ++i) {
			if (s[i] < s[i - 1]) {
				pos = i - 1;
				while (pos > 0 && s[pos] == s[pos - 1]) --pos;
				break;
			}
		}
		if (pos != -1) {
			s[pos]--;
			for (int i = pos + 1; i < s.size(); ++i) {
				s[i] = '9';
			}
		}
		stringstream str(s);
		long long l;
		str >> l;

		ofs << "Case #" << test + 1 << ": " << l << endl;
	}
	return 0;
}
