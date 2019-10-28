#include <algorithm>
#include <functional>
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

using ull = unsigned long long;

class Solution {
public:
  void solve(std::istream &in, std::ostream &out) {
    int T;
    in >> T;
    for (int test = 1; test <= T; ++test) {
      ull n, k;
      in >> n >> k;
      auto p = solve(n, k);
      out << "Case #" << test << ": " << p.second << " " << p.first << "\n";
    }
  }

  pair<ull, ull> solve(ull n, ull k) {
    map<ull, ull, greater<ull>> q;
    q[n] = 1;
    for (;;) {
      auto it = q.begin();
      ull d = it->first - 1;
      ull a = d / 2, b = d - a;
      ull cnt = it->second;
      q.erase(it);
      if (cnt >= k) {
        return {a, b};
      }
      k -= cnt;
      if (a)
        q[a] += cnt;
      if (b)
        q[b] += cnt;
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
