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

const int C[6] = {1, 3, 2, 6, 4, 5};
const string colors = "ROYGBV";

bool crossed(int c1, int c2) { return (C[c1] & C[c2]) != 0; }

bool check(const vector<int> &v) {
  for (int i = 0; i + 1 < v.size(); ++i)
    if (crossed(v[i], v[i + 1]))
      return false;
  if (crossed(v[0], v.back()))
    return false;
  return true;
}

string vtos(const vector<int> &v) {
  string res;
  for (int i : v) {
    res += colors[i];
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  ifstream ifs("b.in");
  ofstream ofs("b.out");

  int t;
  ifs >> t;
  for (int test = 0; test < t; ++test) {
    int n;
    ifs >> n;
    vector<int> v(6);
    for (int i = 0; i < 6; ++i) {
      ifs >> v[i];
    }
    vector<int> res(n);
    int prev = -1;
    for (int i = 0; i < n; ++i) {
      int bestj = -1;
      for (int j = 0; j < 6; ++j) {
        if ((bestj == -1 || v[j] > v[bestj]) && v[j] > 0 &&
            (prev == -1 || !crossed(prev, j)))
          bestj = j;
      }
      if (bestj == -1) {
        for (int j = 0; j < 6; ++j) {
          if ((bestj == -1 || v[j] > v[bestj]) && v[j] > 0)
            bestj = j;
        }
      }
      --v[bestj];
      res[i] = bestj;
      prev = bestj;
    }

    if (!check(res)) {
      sort(res.size() < 10 ? res.begin() : res.end() - 10, res.end());
      do {
        if (check(res))
          break;
      } while (next_permutation(res.size() < 10 ? res.begin() : res.end() - 10,
                                res.end()));
    }
    ofs << "Case #" << test + 1 << ": "
        << (!check(res) ? "IMPOSSIBLE" : vtos(res)) << endl;
  }
  return 0;
}
