#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
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
  int n, k;
  cin >> n >> k;
  double u;
  cin >> u;
  vector<double> p;
  for (__typeof(0) i = (0); i < (n); ++i) {
    double pi;
    cin >> pi;
    p.push_back(pi);
  }
  sort(p.begin(), p.end());

  p.push_back(1.);
  for (__typeof(0) i = (0); i < (n); ++i) {
    double mu = (p[i + 1] - p[i]) * (i + 1);
    if (mu <= u) {
      for (__typeof(0) j = (0); j < (i + 1); ++j) {
        p[j] += p[i + 1] - p[i];
      }
      u -= mu;
    } else {
      for (__typeof(0) j = (0); j < (i + 1); ++j) {
        p[j] += u / (i + 1);
      }
      u = 0.;
      break;
    }
  }

  if (u > 0) {
    for (__typeof(0) i = (0); i < (n); ++i) {
      p[i] = min(1., p[i] + u / n);
    }
  }

  double res = 1.;
  for (__typeof(0) i = (0); i < (n); ++i) {
    res *= p[i];
  }
  return res;
}

int main() {
  int t;
  cin >> t;
  for (int x = 1; x <= t; ++x) {
    cout << "Case #" << x << ": " << setprecision(16) << fixed << solve()
         << endl; // result
  }
  return 0;
}
