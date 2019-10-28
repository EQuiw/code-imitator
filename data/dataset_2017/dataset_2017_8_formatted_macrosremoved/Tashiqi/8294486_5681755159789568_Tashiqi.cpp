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
    long long n, Q, foo, u, v;
    cin >> n >> Q;
    vector<double> E(n), S(n), R(n, -1), D(n - 1);
    for (long long i = 0; i < n; ++i) {
      cin >> E[i] >> S[i];
    }
    for (long long i = 0; i < n; ++i) {
      for (long long j = 0; j < n; ++j) {
        if (i + 1 == j)
          cin >> D[i];
        else
          cin >> foo;
      }
    }
    cin >> u >> v;
    R[0] = 0;
    for (long long i = 0; i < n; ++i) {
      double d = 0;
      for (long long j = i; j < n and d <= E[i]; ++j) {
        if (R[j] == -1 or R[i] + d / S[i] < R[j])
          R[j] = R[i] + d / S[i];
        d += D[j];
      }
    }
    cout << "Case #" << t + 1 << ": " << fixed << setprecision(6) << R[n - 1]
         << endl;
  }
  return 0;
}
