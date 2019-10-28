#include <iostream>

using namespace std;

int solve(int cc) {
  long long d, n, k, s;
  long double mt = 0;
  cin >> d >> n;
  for (int i = 0; i < n; i++) {
    cin >> k >> s;
    long double tt = (d - k);
    tt /= s;
    if (i == 0 || mt < tt) {
      mt = tt;
    }
  }
  cout << "Case #" << cc << ": " << fixed << d / mt << endl;
  return 1;
}

int main() {
  int t;
  cin >> t;
  cout.precision(7);
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
  return 0;
}
