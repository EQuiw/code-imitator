#include <algorithm>
#include <complex>
#include <cstdarg>
#include <cstdio>
#include <functional>
#include <iomanip>
#include <istream>
#include <limits>
#include <map>
#include <numeric>
#include <ostream>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
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
      int N, R, O, Y, G, B, V;
      in >> N >> R >> O >> Y >> G >> B >> V;
      out << "Case #" << test << ": " << solve(N, R, O, Y, G, B, V) << "\n";
    }
  }

  string solve(int N, int R, int O, int Y, int G, int B, int V) {
    if (O || G || V)
      return "";
    if (2 * R > N || 2 * Y > N || 2 * B > N)
      return "IMPOSSIBLE";
    string s(N, '?');
    vector<int> cnt{R, Y, B};
    string col = "RYB";
    int j = 0;
    if (cnt[1] > cnt[j])
      j = 1;
    if (cnt[2] > cnt[j])
      j = 2;
    for (int i = 0; i < N; ++i) {
      int k = (j + 1) % 3;
      if (cnt[k] > cnt[j])
        j = k;
      --cnt[j];
      s[i] = col[j];
      j = (j + 1) % 3;
    }

    if (s.front() == s.back()) {
      swap(s[0], s[1]);
      int i = 2;
      while (i < N && s[i] == s[i - 1]) {
        swap(s[i], s[(i + 1) % N]);
        i += 2;
      }
    }

    for (int i = 0; i < N; ++i)
      if (s[i] == '?' || s[i] == s[(i + 1) % N])
        throw logic_error{"..."};

    return s;
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
