#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
static const long long D = 1000000007;

int main() {
  long long T;
  cin >> T;
  for (long long t = 0; t < T; ++t) {
    double d, k, s, M = 0;
    long long n;
    cin >> d >> n;
    for (long long i = 0; i < n; ++i) {
      cin >> k >> s;
      if (M < (d - k) / s)
        M = (d - k) / s;
    }
    cout << "Case #" << t + 1 << ": " << fixed << setprecision(6) << d / M
         << endl;
  }
  return 0;
}
