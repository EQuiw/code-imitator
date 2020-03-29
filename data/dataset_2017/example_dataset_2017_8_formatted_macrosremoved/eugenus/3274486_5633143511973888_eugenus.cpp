#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, int> par;
typedef long long int tint;

double EPS = 1e-7;
double p[55];

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int t;
  cin >> t;
  int n, k;
  double u;

  cout.setf(ios::showpoint | ios::fixed);
  cout.precision(10);

  for (int caso = (1); caso < (t + 1); caso++) {
    cin >> n >> k;
    cin >> u;
    for (int i = 0; i < (n); i++)
      cin >> p[i];
    double ma = 0.0;
    double P = 0.0;
    for (int i = 0; i < (n); i++) {
      P += p[i];
      ma = max(ma, p[i]);
    }
    double lambda = (u + P) / (n + 0.0);

    double ans;

    if (ma <= lambda) {
      ans = n * log(lambda);
      ans = exp(ans);
    } else {
      double hi = lambda;
      double lo = 0.0;
      while (hi - lo > EPS) {
        double m = (hi + lo) / 2.0;
        double us = 0.0;
        for (int i = 0; i < (n); i++) {
          if (p[i] < m) {
            double dif = m - p[i];
            us += dif;
          }
        }

        if (us < u)
          lo = m;
        else
          hi = m;
      }

      ans = 0.0;
      for (int i = 0; i < (n); i++) {
        if (p[i] < lo)
          ans += log(lo);
        else
          ans += log(p[i]);
      }
      ans = exp(ans);
    }
    cout << "Case #" << caso << ": " << ans << endl;
  }

  return 0;
}
