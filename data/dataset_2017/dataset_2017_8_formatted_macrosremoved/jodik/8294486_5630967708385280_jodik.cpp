#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <complex>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <stdarg.h>
#include <string>
#include <vector>

// M_PI SI TREBA ODLOZIT

using namespace std;

typedef long double ld;

int main() {
  // string m;
  int t;
  long long d, n;
  cin >> t;
  for (int tt = 0; tt < t; tt++) {
    cout << "Case #" << (tt + 1) << ": ";
    cin >> d >> n;
    ld max_time = 0;
    long long di, ki;
    for (int i = 0; i < (n); i++) {
      cin >> di >> ki;
      di = d - di;
      max_time = max((di / (ld)ki), max_time);
    }

    cout << std::fixed << std::setprecision(12) << d / max_time << endl;
  }
}
