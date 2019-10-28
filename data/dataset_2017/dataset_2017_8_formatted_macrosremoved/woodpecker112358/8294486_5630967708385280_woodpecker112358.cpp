#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
typedef long long mint;
typedef unsigned long long umint;
bool willCatch(int sp, int pos, double s, int d) {
  if (sp >= s) {
    return false;
  }
  if (pos * s >= d * (s - sp)) {
    return false;
  }
  return true;
}
int main() {
  freopen("A-small-attempt1.in", "r", stdin);
  freopen("Aout.txt", "w", stdout);
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int d, n;
    cin >> d >> n;
    // cout << d <<" "<<n << endl;
    vector<int> sp(n), pos(n);
    for (int i = 0; i < (n); i++) {
      cin >> pos[i] >> sp[i];
      // cout << pos[i] <<" "<<sp[i] <<endl;
    }
    double lo = 0.0, hi = 10000.0 * 10000000000.0;
    // cout << std::setprecision(10) << std::fixed;
    while ((((hi - lo) < 0) ? (-(hi - lo)) : (hi - lo)) > 1e-10) {
      double mid = (lo + hi) / 2;
      // cout <<fixed <<lo <<" "<<hi << " " << mid <<endl;
      if (mid == lo || mid == hi) {
        break;
      }
      bool ok = true;
      for (int i = 0; i < (n); i++) {
        if (willCatch(sp[i], pos[i], mid, d)) {
          ok = false;
          break;
        }
      }
      // cout << ok << endl;
      if (ok) {
        lo = mid;
      } else {
        hi = mid;
      }
    }
    printf("Case #%d: %.9f\n", t, lo);
  }
  return 0;
}
