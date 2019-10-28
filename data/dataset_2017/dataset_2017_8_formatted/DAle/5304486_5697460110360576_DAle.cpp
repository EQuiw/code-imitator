#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct Int {
  int l, r;
  bool isEmpty() { return l > r; }
};

Int getInt(int count, int need) {
  int minx = (count * 100 + (need * 90 - 1)) / (need * 90) - 1;
  int maxx = (count * 100) / (need * 110) + 1;

  int mn = -1, mx = -1;
  for (int i = 1; i <= 2000000; ++i) {
    if (need * (long long)i * 90 <= count * 100 &&
        count * 100 <= need * (long long)i * 110) {
      if (mn == -1)
        mn = i;
      mx = i;
    }
  }
  if (mn == -1)
    return Int{0, -1};
  return Int{mn, mx};
}

Int cross(const Int &l, const Int &r) {
  return Int{max(l.l, r.l), min(l.r, r.r)};
}

int main() {
  ios_base::sync_with_stdio(false);
  ifstream ifs("b.in");
  ofstream ofs("b.out");

  int t;
  ifs >> t;
  for (int test = 0; test < t; ++test) {
    int res = 0;
    int n, p;
    ifs >> n >> p;
    vector<int> c(n);
    for (int i = 0; i < n; ++i)
      ifs >> c[i];

    vector<vector<int>> v(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < p; ++j) {
        int k;
        ifs >> k;
        v[i].push_back(k);
      }
      sort(v[i].begin(), v[i].end());
    }

    vector<vector<Int>> vi(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < p; ++j) {
        vi[i].push_back(getInt(v[i][j], c[i]));
      }
    }

    vector<vector<int>> was(n, vector<int>(p, 0));
    for (int i = 0; i < p; ++i) {
      Int cur = vi[0][i];
      vector<int> way;
      way.push_back(i);
      bool found = !cur.isEmpty();
      for (int j = 1; j < n; ++j) {
        found = false;
        for (int k = 0; k < p; ++k) {
          if (was[j][k] == 0 && !cross(cur, vi[j][k]).isEmpty()) {
            way.push_back(k);
            cur = cross(cur, vi[j][k]);
            found = true;
            break;
          }
        }
        if (!found) {
          break;
        }
      }
      if (found) {
        for (int i = 0; i < n; ++i) {
          was[i][way[i]] = 1;
        }
        ++res;
      }
    }
    ofs << "Case #" << test + 1 << ": " << res << endl;
  }
  return 0;
}
