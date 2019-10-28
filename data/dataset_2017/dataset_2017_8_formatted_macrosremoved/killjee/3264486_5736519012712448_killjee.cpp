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

long long a[1005];

ll main() {
  freopen("Task.in", "r", stdin);
  freopen("Task.out", "w", stdout);
  long long t;
  cin >> t;
  long long cc = 1;

  while (t--) {
    string s;
    long long k;
    cin >> s >> k;

    for (long long i = 0; i < ((long long)s.size()); i++) {
      if (s[i] == '-')
        a[i] = 1;
      else
        a[i] = 0;
    }

    long long cnt = 0;

    for (long long i = ((long long)s.size()) - 1; i >= 0; i--) {
      if (a[i] == 0)
        continue;
      if (i < k - 1)
        break;
      cnt++;
      for (long long j = i, p = 0; p < k; p++, j--) {
        a[j] = (a[j] + 1) % 2;
      }
    }

    bool flag = 0;

    for (long long i = 0; i < ((long long)s.size()); i++) {
      // cout<<a[i]<<" ";
      if (a[i] == 1)
        flag = 1;
    }
    cout << "Case #" << cc << ": ";
    cc++;
    if (flag)
      cout << "Impossible\n";
    else
      cout << cnt << endl;
  }
}
