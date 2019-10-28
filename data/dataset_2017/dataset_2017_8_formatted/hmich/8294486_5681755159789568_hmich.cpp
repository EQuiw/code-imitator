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
ifstream in("c.in");
#else
istream &in = cin;
#endif
// ostream & out = cout;
ofstream out("c.out");
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
    int n, q;
    in >> n >> q;
    vd e(n), s(n);
    for (int i = 0; i < n; ++i)
      in >> e[i] >> s[i];
    double inf = 1e20;
    vvd d(n, vd(n, inf));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int x;
        in >> x;
        if (x != -1)
          d[i][j] = x;
      }
    }
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        for (int k = 0; k < n; ++k)
          d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
    vvd time(n, vd(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j)
        if (d[i][j] > e[i]) {
          d[i][j] = inf;
          time[i][j] = inf;
        } else
          time[i][j] = d[i][j] / s[i];
    }
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        for (int k = 0; k < n; ++k)
          time[j][k] = min(time[j][k], time[j][i] + time[i][k]);
    out << "Case #" << test << ": ";
    for (int i = 0; i < q; ++i) {
      int u, v;
      in >> u >> v;
      --u;
      --v;
      out.setf(ios::fixed);
      out.precision(10);
      out << time[u][v] << ' ';
    }
    out << '\n';
  }
  return 0;
}
