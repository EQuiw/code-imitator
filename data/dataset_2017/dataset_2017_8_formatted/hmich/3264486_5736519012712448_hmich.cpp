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
#pragma warning(disable : 4244 4267 4018 4996 4800)
//#pragma comment( linker, "/stack:10000000" )
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef pair<int, int> pii;
#define all(v) begin(v), end(v)

#ifdef LOCAL
ifstream in("a.in");
#else
istream &in = cin;
#endif
// ostream & out = cout;
ofstream out("a.out");
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
    int k;
    in >> s >> k;
    vi v(s.size());
    int res = 0;
    bool possible = true;
    for (int i = 0; i < s.size(); ++i) {
      int cnt = 0;
      for (int j = i - 1; j >= i - k + 1 && j >= 0; --j)
        cnt += v[j];
      if ((cnt & 1) == (s[i] == '+')) {
        if (i <= s.size() - k)
          v[i] = 1, ++res;
        else
          possible = false;
      }
    }
    out << "Case #" << test << ": ";
    if (!possible)
      out << "IMPOSSIBLE";
    else
      out << res;
    out << '\n';
  }
  return 0;
}
