#include <bits/stdc++.h>
#define TR(c, it) for (__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define FOR(i, a, b) for (int i = (a), _b = (b); i < _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define FORE(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define SZ(c) (int)(c).size()

using namespace std;

const int N = 1010;

int D, n;
pair<int, int> horses[N];

int main() {
  // freopen("A.inp", "r", stdin);
  // freopen("A.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int tests;
  cin >> tests;
  for (int test = 1; test <= tests; ++test) {
    cin >> D >> n;
    for (int i = 0; i < n; ++i) {
      cin >> horses[i].first >> horses[i].second;
    }
    sort(horses, horses + n);
    double t = 0.0;
    double d = (double)D;
    for (int i = n - 1; i >= 0; --i) {
      double ki = horses[i].first;
      double vi = horses[i].second;
      if (ki + vi * t < d) {
        t = (d - ki) / vi;
      }
    }
    double ans = d / t;
    cout << "Case #" << test << ": " << setprecision(17) << ans << endl;
  }
  return 0;
}
