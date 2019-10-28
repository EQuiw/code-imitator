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

int main() {
  ios_base::sync_with_stdio(false);
  int ntests;
  in >> ntests;
  for (int test = 1; test <= ntests; ++test) {
    string s;
    in >> s;
    string ans;
    int i = 0;
    for (i = 0; i < s.size(); ++i) {
      if (s[i] > '0' && (i == 0 || s[i] - 1 >= s[i - 1]))
        ans = s.substr(0, i) + char(s[i] - 1) + string(s.size() - i - 1, '9');
      if (i > 0 && s[i] < s[i - 1])
        break;
    }
    if (i == s.size())
      ans = s;
    while (ans[0] == '0')
      ans = ans.substr(1);
    out << "Case #" << test << ": " << ans << '\n';
  }
  return 0;
}
