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
    cout << "Case #" << cc << ": ";
    cc++;
    long long n;
    cin >> n;
    for (long long i = n; i >= 1; i--) {
      string s = "";
      long long p = i;
      while (p != 0) {
        long long b = p % 10;
        char c = b + '0';
        s = c + s;
        p /= 10;
      }
      bool ch = 0;
      for (long long j = 1; j < s.size(); j++) {
        if (s[j] < s[j - 1]) {
          ch = 1;
          break;
        }
      }
      if (!ch) {
        cout << i << endl;
        break;
      }
    }
  }
}
