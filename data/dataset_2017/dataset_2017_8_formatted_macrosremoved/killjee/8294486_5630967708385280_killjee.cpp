#include <bits/stdc++.h>
using namespace std;

typedef int ll;
typedef pair<long long, long long> pii;
typedef pair<long long, pair<long long, long long>> piii;

const long long mod = 1e9 + 7;

long long POWER[65];
long long power(long long a, long long b) {
  long long ret = 1;
  while (b) {
    if (b & 1)
      ret *= a;
    a *= a;
    if (ret >= mod)
      ret %= mod;
    if (a >= mod)
      a %= mod;
    b >>= 1;
  }
  return ret;
}
long long inv(long long x) { return power(x, mod - 2); }

void precompute() {
  POWER[0] = 1;
  for (long long i = 1; i < 63; i++)
    POWER[i] = POWER[i - 1] << 1LL;
}

ll main() {
  freopen("Task.in", "r", stdin);
  freopen("Task.out", "w", stdout);
  long long t, cc = 1;
  cin >> t;

  while (t--) {
    long long d, n;
    cin >> d >> n;

    double tim = 0;
    for (long long i = 0; i < n; i++) {
      long long a, b;
      cin >> a >> b;
      double ti = (d - a) / ((double)b);
      tim = max(ti, tim);
    }
    cout << setprecision(10) << fixed << "Case #" << cc << ": " << d / tim
         << endl;
    cc++;
  }
}
