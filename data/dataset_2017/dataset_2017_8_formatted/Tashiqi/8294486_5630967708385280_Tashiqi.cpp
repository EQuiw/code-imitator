#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>
#define ll long long
#define sort(A) sort(A.begin(), A.end())
#define rsort(A) sort(A.rbegin(), A.rend())
using namespace std;
static const ll D = 1000000007;

int main() {
  ll T;
  cin >> T;
  for (ll t = 0; t < T; ++t) {
    double d, k, s, M = 0;
    ll n;
    cin >> d >> n;
    for (ll i = 0; i < n; ++i) {
      cin >> k >> s;
      if (M < (d - k) / s)
        M = (d - k) / s;
    }
    cout << "Case #" << t + 1 << ": " << fixed << setprecision(6) << d / M
         << endl;
  }
  return 0;
}
