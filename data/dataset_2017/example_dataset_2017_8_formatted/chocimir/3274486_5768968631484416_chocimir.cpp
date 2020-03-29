#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef long double LD;

#define FOR(k, a, b) for (__typeof(a) k = (a); k < (b); ++k)
#define dprintf(...) fprintf(stderr, __VA_ARGS__)

int cond = 1;
#define DB(X)                                                                  \
  {                                                                            \
    if (cond) {                                                                \
      cerr << "Line:" << __LINE__ << ", " << #X << " = " << X << endl;         \
    }                                                                          \
  }

double solve() {
  int n, k;
  cin >> n >> k;
  vector<pair<LL, LL>> v;
  LL r, h;
  FOR(i, 0, n) {
    cin >> r >> h;
    v.push_back({r, h});
  }
  sort(v.rbegin(), v.rend());

  LL res = 0LL;
  FOR(i, 0, n) {
    LL rh = v[i].first * v[i].second * 2;
    LL cs = rh + v[i].first * v[i].first;
    vector<LL> rhs;
    FOR(j, i + 1, n) { rhs.push_back(v[j].first * v[j].second * 2); }
    int a = rhs.size();
    if (rhs.size() >= k - 1) {
      sort(rhs.begin(), rhs.end());
      for (int j = 1; j < k; ++j) {
        cs += rhs[a - j];
      }
      if (res < cs)
        res = cs;
    }
  }

  return M_PI * res;
}

int main() {
  int t;
  cin >> t;
  FOR(x, 1, t + 1) {
    cout << "Case #" << x << ": " << setprecision(16) << fixed << solve()
         << endl; // result
  }
  return 0;
}
