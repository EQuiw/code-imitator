#include <algorithm>
#include <iomanip>
#include <istream>
#include <map>
#include <numeric>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
// Powered by caide (code generator, tester, and library code inliner)


class Solution {
public:
    void solve(std::istream& in, std::ostream& out) {
		int T; in >> T;
		for (int test = 1; test <= T; ++test) {
			string s; in >> s;
			int n = s.size();
			for (;;) {
				int i = 0;
				while (i + 1 < n && s[i] <= s[i + 1])
					++i;
				if (i + 1 == n)
					break;
				--s[i];
				for (++i; i < n; ++i)
					s[i] = '9';
			}

			while (s[0] == '0')
				s = s.substr(1);
			out << "Case #" << test << ": " << s << "\n";
		}
    }
};

void solve(std::istream& in, std::ostream& out)
{
    out << std::setprecision(12);
    Solution solution;
    solution.solve(in, out);
}


#include <fstream>
#include <iostream>


int main() {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);


    istream& in = cin;


    ostream& out = cout;

    solve(in, out);
    return 0;
}


