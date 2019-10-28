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
    ll n, k;
    in >> n >> k;
    map<ll, ll> m;
    m[n] = 1;
    ll l, r;
    while (true) {
      auto it = m.end();
      --it;
      ll w = it->first;
      ll cnt = it->second;
      l = w / 2, r = max(0LL, w - 1) / 2;
      if (k > cnt) {
        m.erase(it);
        m[l] += cnt;
        m[r] += cnt;
        k -= cnt;
      } else
        break;
    }
    out << "Case #" << test << ": " << l << ' ' << r << '\n';
  }
  return 0;
}
