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

#include <random>

#include <complex>

#include <functional>

#include <cstdarg>
#include <cstdio>

#include <stack>

#include <limits>

#include <tuple>

int iceil(int a, int b) { return (a + b - 1) / b; }

class Solution {
public:
  void solve(std::istream &in, std::ostream &out) {
    int T;
    in >> T;
    for (int test = 1; test <= T; ++test) {
      int n, p;
      in >> n >> p;
      vector<int> r(n);
      for (int &i : r)
        in >> i;
      vector<vector<int>> q(n, vector<int>(p));
      for (auto &v : q)
        for (int &i : v)
          in >> i;

      vector<int> perm(p);
      int res = 0;
      iota(perm.begin(), perm.end(), 0);
      do {
        int cur = 0;
        for (int i = 0; i < p; ++i) {
          int p1 = q[0][i];
          int r1 = r[0];
          int up = 10 * p1 / (9 * r1);
          int down = iceil(10 * p1, 11 * r1);
          if (n == 2) {
            int p2 = q[1][perm[i]];
            int r2 = r[1];
            up = min(up, 10 * p2 / (9 * r2));
            down = max(down, iceil(10 * p2, 11 * r2));
          }
          if (up >= down && up >= 1)
            ++cur;
        }
        res = max(res, cur);
      } while (next_permutation(perm.begin(), perm.end()));
      out << "Case #" << test << ": " << res << endl;
    }
  }
};

void solve(std::istream &in, std::ostream &out) {
  out << std::setprecision(12);
  Solution solution;
  solution.solve(in, out);
}

#include <fstream>
#include <iostream>

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);

  istream &in = cin;

  ostream &out = cout;

  solve(in, out);
  return 0;
}

#include <cstdlib>
