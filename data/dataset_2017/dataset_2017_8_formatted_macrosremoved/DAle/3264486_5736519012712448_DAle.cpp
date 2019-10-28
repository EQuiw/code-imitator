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
    string s;
    int k;
    ifs >> s >> k;

    int res = 0;
    for (int i = 0; i < s.length() - k + 1; ++i) {
      if (s[i] == '-') {
        for (int j = 0; j < k; ++j) {
          if (s[i + j] == '-')
            s[i + j] = '+';
          else
            s[i + j] = '-';
        }
        ++res;
      }
    }

    bool ok = s.find('-') == -1;
    ofs << "Case #" << test + 1 << ": " << (ok ? to_string(res) : "IMPOSSIBLE")
        << endl;
  }
  return 0;
}
