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

#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define REP(i, b) for (int i = 0; i < (b); i++)
#define ll long long
#define nl printf("\n")

// M_PI SI TREBA ODLOZIT

using namespace std;

typedef long double ld;

string remove_leading_zeros(string m) {
  string res;
  bool zero = true;
  REP(i, m.size()) {
    if (m[i] != '0')
      zero = false;
    if (!zero)
      res += m[i];
  }
  return res;
}

string solve(string m) {
  REP(i, m.size() - 1) {
    if (m[i] > m[i + 1]) {
      while (i > 0 && m[i - 1] >= m[i]) {
        i--;
      }
      char c = m[i] - 1;
      m[i] = c;
      c = '9';
      FOR(j, i + 1, m.size()) { m[j] = c; }
      break;
    }
  }
  return m;
}

int main() {
  string m;
  int t, k;
  cin >> t;
  for (int tt = 0; tt < t; tt++) {
    cin >> m;
    m = solve(m);
    m = remove_leading_zeros(m);

    cout << "Case #" << (tt + 1) << ": " << m << endl;
  }
}