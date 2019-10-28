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
    double res = 0;
    int d, n;
    ifs >> d >> n;
    double maxt = 0;
    for (int i = 0; i < n; ++i) {
      int k, s;
      ifs >> k >> s;

      maxt = max(maxt, (d - k) / (double)s);
    }
    ofs << "Case #" << test + 1 << ": " << setprecision(10) << fixed << d / maxt
        << endl;
  }
  return 0;
}
