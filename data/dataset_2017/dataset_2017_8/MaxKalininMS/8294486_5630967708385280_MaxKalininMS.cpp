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
#include <random>
#include <complex>
#include <functional>
#include <cstdarg>
#include <cstdio>
#include <stack>
#include <limits>
#include <tuple>

using namespace std;
// Powered by caide (code generator, tester, and library code inliner)


class Solution {
public:
    void solve(std::istream& in, std::ostream& out) {
		int T; in >> T;
		for (int test = 1; test <= T; ++test) {
			double D; int n; in >> D >> n;
			vector<double> K(n), S(n);
			double res = std::numeric_limits<double>::max();
			for (int i = 0; i < n; ++i) {
				in >> K[i] >> S[i];
				res = min(res, D / (D - K[i]) * S[i]);
			}

			out << "Case #" << test << ": " << res << "\n";
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


#include <cstdlib>


