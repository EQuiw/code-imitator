/*input
3
2525 1
2400 5
300 2
120 60
60 90
100 2
80 100
70 10
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
long long S, n;
vector<pair<long long, long long>> a;

bool check(double speed) {
  for (long long i = 0; i < a.size(); i++) {
    double left = S - a[i].first;
    if (double(S) / speed < left / (double)(a[i].second))
      return false;
  }
  return true;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  long long T;
  cin >> T;
  long long ct = 0;
  while (T--) {
    ct++;
    a.clear();
    cin >> S >> n;
    for (long long i = 1; i <= n; i++) {
      long long x, y;
      cin >> x >> y;
      a.push_back(make_pair(x, y));
    }
    double l = 0, r = 3e18;
    for (long long j = 1; j <= 200; j++) {
      double mid = (l + r) / 2.0;
      if (check(mid))
        l = mid;
      else
        r = mid;
    }
    cout << "Case #" << ct << ": ";
    cout << setprecision(10) << fixed << l << '\n';
  }
}
