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

#define forn(i, n) for (int i = 0; i < (n); i++)
#define forsn(i, s, n) for (int i = (s); i < (n); i++)
#define all(v) ((v).begin, (v).end)
#define pb push_back
#define x first
#define y second
#define mp make_pair

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

  forsn(caso, 1, t + 1) {
    cin >> n >> k;
    cin >> u;
    forn(i, n) cin >> p[i];
    double ma = 0.0;
    double P = 0.0;
    forn(i, n) {
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
        forn(i, n) {
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
      forn(i, n) {
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