#include <cmath>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    unsigned long long int n, k;
    unsigned long long int k0 = 1;
    cin >> n >> k;
    while (k0 <= k / 2)
      k0 *= 2;
    unsigned long long int q, r, s;
    q = (n - k0 + 1) / k0;
    r = (n - k0 + 1) % k0;
    if (k - k0 < r)
      s = q + 1;
    else
      s = q;
    cout << "Case #" << i + 1 << ": " << s / 2 << ' ' << (s - 1) / 2 << '\n';
  }
}
