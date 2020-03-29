#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
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

int solve() {
  int ac, aj;
  cin >> ac >> aj;
  vector<pair<pair<int, int>, int>> as;
  int cjl[2] = {720, 720};
  for (__typeof(0) i = (0); i < (ac); ++i) {
    int c, d;
    cin >> c >> d;
    as.push_back({{c, d}, 0});
    cjl[0] -= (d - c);
  }
  for (__typeof(0) i = (0); i < (aj); ++i) {
    int c, d;
    cin >> c >> d;
    as.push_back({{c, d}, 1});
    cjl[1] -= (d - c);
  }

  int res = 0;
  sort(as.begin(), as.end());
  as.push_back({{24 * 60 + as[0].first.first, 24 * 60 + as[0].first.second},
                as[0].second});
  vector<int> le[2];
  for (__typeof(0) i = (0); i < (as.size() - 1); ++i) {
    if (as[i].second == as[i + 1].second) {
      res += 2;
      le[as[i].second].push_back(as[i + 1].first.first - as[i].first.second);
    } else {
      res += 1;
    }
  }
  for (__typeof(0) i = (0); i < (2); ++i) {
    sort(le[i].begin(), le[i].end());
    for (__typeof(0) j = (0); j < (le[i].size()); ++j) {
      if (cjl[i] >= le[i][j]) {
        cjl[i] -= le[i][j];
        res -= 2;
      }
    }
  }

  return res;
}

int solve2() {

  int ac, aj;
  cin >> ac >> aj;
  vector<pair<int, int>> as;
  int cjl[2] = {720, 720};
  for (__typeof(0) i = (0); i < (ac); ++i) {
    int c, d;
    cin >> c >> d;
    as.push_back({c, d});
    cjl[0] -= (d - c);
  }
  for (__typeof(0) i = (0); i < (aj); ++i) {
    int c, d;
    cin >> c >> d;
    as.push_back({c, d});
    cjl[1] -= (d - c);
  }

  sort(as.begin(), as.end());
  if (ac == aj) {
    return 2;
  }

  if (ac + aj == 1) {
    return 2;
  }

  if (as[1].second - as[0].first <= 720) {
    return 2;
  }

  if (24 * 60 + as[0].first - as[1].second <= 720) {
    return 2;
  }

  return 4;
}

int main() {
  int t;
  cin >> t;
  for (int x = 1; x <= t; ++x) {
    cout << "Case #" << x << ": " << solve() << endl; // result
  }
  return 0;
}
