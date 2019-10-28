#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<string> vs;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef pair<int, int> pii;
#define all(v) begin(v), end(v)

#ifdef LOCAL
ifstream in("b.in");
#else
istream &in = cin;
#endif
// ostream & out = cout;
ofstream out("b.out");
template <class T> void read(T &t) {
  for (auto &x : t)
    in >> x;
}
template <class T> int sz(T const &t) { return (int)t.size(); }

bool put(vector<char> &s, char a, char b, char c) {
  for (int i = 0; i < s.size(); ++i) {
    int ii = i + 1;
    if (ii == s.size())
      ii = 0;
    if ((s[i] == b || s[i] == c) && (s[ii] == b || s[ii] == c)) {
      s.insert(s.begin() + i + 1, a);
      return true;
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  int ntests;
  in >> ntests;
  for (int test = 1; test <= ntests; ++test) {
    int n, r, o, y, g, b, v;
    in >> n >> r >> o >> y >> g >> b >> v;
    if (test != 1)
      out << "\n";
    out << "Case #" << test << ": ";

    if (o == 0 && g == 0 && r == b && v == 0 && y == 0) {
      for (int i = 0; i < r; ++i)
        out << "RB";
      continue;
    }
    if (o == 0 && b == 0 && g == 0 && r == y && v == 0) {
      for (int i = 0; i < r; ++i)
        out << "RY";
      continue;
    }
    if (o == 0 && g == 0 && r == 0 && v == 0 && y == b) {
      for (int i = 0; i < y; ++i)
        out << "YB";
      continue;
    }

    if (o == b && g == 0 && r == 0 && v == 0 && y == 0) {
      for (int i = 0; i < o; ++i)
        out << "OB";
      continue;
    }
    if (o == 0 && b == 0 && g == r && v == 0 && y == 0) {
      for (int i = 0; i < g; ++i)
        out << "GR";
      continue;
    }
    if (o == 0 && b == 0 && g == 0 && r == 0 && v == y) {
      for (int i = 0; i < v; ++i)
        out << "VY";
      continue;
    }
    vector<char> s;
    s.reserve(n);
    if (r) {
      s.push_back('R');
      --r;
      for (int i = 0; i < g; ++i) {
        s.push_back('G');
        s.push_back('R');
        --r;
      }
      if (r < 0)
        goto impossible;
    }
    if (b) {
      s.push_back('B');
      --b;
      for (int i = 0; i < o; ++i) {
        s.push_back('O');
        s.push_back('B');
        --b;
      }
      if (b < 0)
        goto impossible;
    }
    if (y) {
      s.push_back('Y');
      --y;
      for (int i = 0; i < v; ++i) {
        s.push_back('V');
        s.push_back('Y');
        --y;
      }
      if (y < 0)
        goto impossible;
    }
    while (r || y || b) {
      bool res = false;
      if (r && put(s, 'R', 'Y', 'B'))
        --r, res = true;
      if (y && put(s, 'Y', 'R', 'B'))
        --y, res = true;
      if (b && put(s, 'B', 'R', 'Y'))
        --b, res = true;
      if (!res)
        goto impossible;
    }
    for (int i = 0; i < n; ++i) {
      int ii = i + 1;
      if (ii == n)
        ii = 0;
      assert(s[i] != s[ii]);
      out << s[i];
    }
    continue;
  impossible:
    out << "IMPOSSIBLE";
  }
  return 0;
}
