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

int cond = 1;

double solve() {
  int n, k;
  cin >> n >> k;
  vector<pair<LL, LL>> v;
  LL r, h;
  for (__typeof(0) i = (0); i < (n); ++i) {
    cin >> r >> h;
    v.push_back({r, h});
  }
  sort(v.rbegin(), v.rend());

  LL res = 0LL;
  for (__typeof(0) i = (0); i < (n); ++i) {
    LL rh = v[i].first * v[i].second * 2;
    LL cs = rh + v[i].first * v[i].first;
    vector<LL> rhs;
    for (__typeof(i + 1) j = (i + 1); j < (n); ++j) {
      rhs.push_back(v[j].first * v[j].second * 2);
    }
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
  for (__typeof(1) x = (1); x < (t + 1); ++x) {
    cout << "Case #" << x << ": " << setprecision(16) << fixed << solve()
         << endl; // result
  }
  return 0;
}
