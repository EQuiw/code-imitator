#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ii> vii;

const int MAXN = 1200;
int n;
ll D;
ll phorse[MAXN];
double vhorse[MAXN];

bool check(double v) {

  for (int i = 0; i < n; i++) {
    if (vhorse[i] >= v)
      continue;

    double x = v * phorse[i] / (v - vhorse[i]);
    if (x < D)
      return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ;
  int T;

  cin >> T;

  for (int test = 1; test < T + 1; test++) {
    cout << "Case #" << test << ": ";
    cin >> D >> n;
    for (int i = 0; i < n; i++) {
      cin >> phorse[i] >> vhorse[i];
    }
    double lo = 0.0;
    double hi = 1e16;
    for (int ii = 0; ii < 120; ii++) {
      double mid = (lo + hi) / 2.0;
      if (check(mid)) {
        lo = mid;
      } else {
        hi = mid;
      }
    }
    double res = (lo + hi) / 2.0;
    cout << setprecision(12) << fixed << res << endl;
  }

  return 0;
}
