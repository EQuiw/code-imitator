#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
static const long long D = 1000000007;

long long foo(long long n, long long k) {
  if (k == 0)
    return n;
  else {
    return max(foo(n / 2, k / 2), foo((n - 1) / 2, (k - 1) / 2));
  }
}

int main() {
  long long T, n, k;
  cin >> T;
  for (long long t = 0; t < T; ++t) {
    cin >> n >> k;
    long long r = foo(n, k - 1);
    cout << "Case #" << t + 1 << ": " << r / 2 << " " << (r - 1) / 2 << endl;
  }
  return 0;
}
