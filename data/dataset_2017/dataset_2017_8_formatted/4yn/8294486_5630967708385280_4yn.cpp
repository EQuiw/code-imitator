#include <bits/stdc++.h>
using namespace std;
#define eps 0.0000005f
typedef long long int lli;
typedef pair<lli, lli> pii;
typedef double dbl;

int tc;

lli d, n, a, b;
vector<pii> ks;

int main() {
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    ks.clear();
    cin >> d >> n;
    dbl lb, ub, ex;
    lb = 0;
    ub = 0;
    for (int i = 0; i < n; i++) {
      cin >> a >> b;
      ks.push_back(pii(a, b));
      if (ub == 0) {
        if (a != d) {
          ub = d * b / (d - a + 0.0);
        }
      } else if (a != d) {
        ub = min(ub, d * b / (d - a + 0.0));
      }
    }
    while (abs(ub - lb) > eps) {
      ex = (ub + lb) / 2;
      bool f = true;
      // cout << "Testing " << ex << endl;
      for (int i = 0; i < n; i++) {
        // cout << "Horse " << i << " speed " << ks[i].second << endl;
        if (ks[i].second >= ex)
          continue;
        // cout << "Comparative speed: " << ex - ks[i].second << endl;
        // cout << "Intersects at " << ks[i].first / (ex - ks[i].second) * ex <<
        // endl;
        if (ks[i].first / (ex - ks[i].second) * ex < d) {
          f = false;
        }
      }
      if (f) {
        lb = ex;
      } else {
        ub = ex;
      }
    }
    cout << fixed << setprecision(7) << "Case #" << t << ": " << ub << endl;
  }
}