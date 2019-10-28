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
  void solve(std::istream &in, std::ostream &out) {
    int T;
    in >> T;
    for (int test = 1; test <= T; ++test) {
      out << "Case #" << test << ": ";
      string s;
      int K;
      in >> s >> K;
      int n = s.length();
      int res = 0, i;
      for (i = 0; i + K <= n; ++i)
        if (s[i] == '-') {
          ++res;
          for (int j = i; j < i + K; ++j) {
            s[j] = s[j] == '+' ? '-' : '+';
          }
        }
      for (; i < n; ++i)
        if (s[i] == '-')
          res = -1;
      if (res < 0)
        out << "IMPOSSIBLE";
      else
        out << res;
      out << "\n";
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
