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


namespace caide {

template<typename C>
int SZ(const C& c) { return (int)c.size(); }


}


using namespace caide;


class Solution {
public:
    void solve(std::istream& in, std::ostream& out) {
		int T; in >> T;
		for (int test = 1; test <= T; ++test) {

			int R, C; in >> R >> C;
			vector<string> grid(R);
			for (auto& s : grid)
				in >> s;

			fill(grid);
			out << "Case #" << test << ":" << endl;
			for (const string& s : grid) {
				out << s << endl;
			}
		}
    }

	void fill(vector<string>& grid) {
		int maxi = 0;
		for (int i = 0; i < SZ(grid); ++i) for (char c : grid[i]) if (c != '?')
			maxi = i;
		for (int i = 0; i < SZ(grid); ++i) for (int j = 0; j < SZ(grid[i]); ++j) if (grid[i][j] != '?') {
			int il = i, jl = j, ir = i, jr = j;
			while (il > 0 && all(grid, il-1, ir, jl, jr, grid[i][j]))
				--il;
			while (jl > 0 && all(grid, il, ir, jl-1, jr, grid[i][j]))
				--jl;
			if (i == maxi) while (ir < SZ(grid)-1 && all(grid, il, ir+1, jl, jr, grid[i][j]))
				++ir;
			while (jr < SZ(grid[i]) - 1 && all(grid, il, ir, jl, jr+1, grid[i][j]))
				++jr;
			fill(grid, il, ir, jl, jr, grid[i][j]);
		}
		for (auto& s : grid) for (char c : s) if (c == '?') {
			throw std::logic_error{ "..." };
		}
	}
	bool all(const vector<string>& grid, int il, int ir, int jl, int jr, char c) {
		for (int i = il; i <= ir; ++i) for (int j = jl; j <= jr; ++j)
			if (grid[i][j] != c && grid[i][j] != '?')
				return false;

		return true;
	}
	void fill(vector<string>& grid, int il, int ir, int jl, int jr, char c) {
		for (int i = il; i <= ir; ++i) for (int j = jl; j <= jr; ++j)
			grid[i][j] = c;
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


