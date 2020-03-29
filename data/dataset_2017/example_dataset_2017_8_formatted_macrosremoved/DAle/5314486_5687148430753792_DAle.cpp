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
  ifstream ifs("b.in");
  ofstream ofs("b.out");

  int t;
  ifs >> t;
  for (int test = 0; test < t; ++test) {
    int res = 0;
    int n, c, m;
    ifs >> n >> c >> m;
    vector<int> v[2];
    v[0].assign(n, 0);
    v[1].assign(n, 0);

    for (int i = 0; i < m; ++i) {
      int p, b;
      ifs >> p >> b;
      --p;
      --b;
      v[b][p]++;
    }

    int ch = 0;
    while (true) {
      int i = 0;
      for (; i < n; ++i) {
        if (v[0][i] > 0 && v[1][i] > 0) {
          break;
        }
      }
      if (i < n) {
        int f = v[0][i] < v[1][i] ? 0 : 1;
        bool found = false;
        for (int j = i + 1; j < n; ++j) {
          if (v[1 - f][j] < v[f][j] && v[1 - f][j] > 0) {
            found = true;
            --v[f][i];
            --v[1 - f][j];
            ++res;
            break;
          }
        }
        if (!found) {
          for (int j = 0; j < n; ++j) {
            if (i != j && v[1 - f][j] > 0) {
              found = true;
              --v[f][i];
              --v[1 - f][j];
              ++res;
              break;
            }
          }
        }
        if (!found) {
          for (int j = 0; j < n; ++j) {
            if (i != j && v[f][j] > 0) {
              found = true;
              v[1 - f][i]--;
              v[f][j]--;
              ++res;
              break;
            }
          }
        }
        if (!found) {
          if (i == 0) {
            res += v[0][i] + v[1][i];
          } else {
            res += max(v[0][i], v[1][i]);
            ch = min(v[0][i], v[1][i]);
          }
          break;
        }
      } else {
        int fsum = accumulate(v[0].begin(), v[0].end(), 0);
        int ssum = accumulate(v[1].begin(), v[1].end(), 0);
        res += max(fsum, ssum);
        break;
      }
    }
    ofs << "Case #" << test + 1 << ": " << res << ' ' << ch << endl;
  }
  return 0;
}
