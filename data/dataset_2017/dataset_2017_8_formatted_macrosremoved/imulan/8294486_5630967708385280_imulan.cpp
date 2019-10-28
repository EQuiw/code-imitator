#include <bits/stdc++.h>
using namespace std;
using ll = long long;

double solve() {
  int d, n;
  cin >> d >> n;

  double t = 0;
  for (int(i) = 0; (i) < (int)(n); ++(i)) {
    int k, s;
    cin >> k >> s;

    double dist = d - k;
    double tmp = dist / s;
    t = max(t, tmp);
  }

  return d / t;
}

int main() {
  int T;
  cin >> T;
  for (int(t) = 0; (t) < (int)(T); ++(t)) {
    printf("Case #%d: %.10f\n", t + 1, solve());
  }
  return 0;
}
