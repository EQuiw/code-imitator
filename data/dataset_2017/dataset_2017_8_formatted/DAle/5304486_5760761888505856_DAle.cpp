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

int main() {
  ios_base::sync_with_stdio(false);
  ifstream ifs("a.in");
  ofstream ofs("a.out");

  int t;
  ifs >> t;
  for (int test = 0; test < t; ++test) {
    int res = 0;
    int n, m;
    ifs >> n >> m;
    vector<string> v(n);

    for (int i = 0; i < n; ++i)
      ifs >> v[i];

    bool found = false;
    int sx;
    for (int i = 0; i < n && !found; ++i)
      for (int j = 0; j < m; ++j)
        if (v[i][j] != '?') {
          sx = i;
          found = true;
          break;
        }

    for (int i = sx; i < n; ++i) {
      char f = '?';
      for (int j = 0; j < m; ++j)
        if (v[i][j] != '?') {
          f = v[i][j];
          break;
        }
      if (f != '?') {
        for (int j = 0; j < m; ++j) {
          if (v[i][j] == '?' || v[i][j] == f) {
            v[i][j] = f;
          } else {
            f = v[i][j];
          }
        }
      } else {
        v[i] = v[i - 1];
      }
    }

    for (int i = 0; i < sx; ++i)
      v[i] = v[sx];
    ofs << "Case #" << test + 1 << ":" << endl;
    for (auto s : v) {
      ofs << s << endl;
    }
  }
  return 0;
}
