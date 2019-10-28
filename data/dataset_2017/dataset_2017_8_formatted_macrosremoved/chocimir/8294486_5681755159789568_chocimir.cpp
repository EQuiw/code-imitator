#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef long double LD;

int cond = 1;

double solve() {
  int n, q;
  vector<long long> e, s, d;
  cin >> n >> q;
  for (int i = 0; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    e.push_back(a);
    s.push_back(b);
  }
  d.push_back(0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int di;
      cin >> di;
      if (di != -1) {
        d.push_back(d.back() + di);
      }
    }
  }

  int a, b;
  cin >> a >> b;
  vector<double> dd;
  dd.push_back(0.);
  for (int i = 1; i < n; ++i) {
    double dm = 1000LL * 1000 * 1000 * 1000 + 5;
    for (int j = 0; j < i; ++j) {
      if (d[i] - d[j] <= e[j]) {
        double tmp = dd[j] + ((double)(d[i] - d[j])) / s[j];
        dm = dm > tmp ? tmp : dm;
      }
    }
    dd.push_back(dm);
  }
  return dd[n - 1];
}

int main() {
  int t;
  cin >> t;
  for (int x = 1; x <= t; ++x) {
    cout.precision(9);
    cout << "Case #" << x << ": " << fixed << solve() << endl; // result
  }
  return 0;
}
