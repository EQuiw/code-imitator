#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <complex>
#include <functional>
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

char opposite(char c) {
  if (c == '-')
    return '+';
  else
    return '-';
}

int main() {
  string m;
  int t, k;
  cin >> t;
  for (int tt = 0; tt < t; tt++) {
    cin >> m >> k;

    // cout<<m<<endl;
    int sol = 0;
    for (int i = 0; i < (m.size() - k + 1); i++) {
      if (m[i] == '-') {
        sol++;
        for (int j = (i); j <= (i + k - 1); j++) {
          m[j] = opposite(m[j]);
        }
      }
    }
    bool je = true;
    for (int i = 0; i < (m.size()); i++) {
      if (m[i] == '-') {
        cout << "Case #" << (tt + 1) << ": IMPOSSIBLE\n";
        je = false;
        break;
      }
    }
    if (je)
      cout << "Case #" << (tt + 1) << ": " << sol << endl;
  }
}
