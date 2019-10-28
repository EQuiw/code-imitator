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

vector<long long> dis, sp;
double DP[155];
long long a[155];

ll main() {
  freopen("Task.in", "r", stdin);
  freopen("Task.out", "w", stdout);
  long long t, cc = 1;
  cin >> t;

  while (t--) {
    dis.clear();
    sp.clear();
    long long n, q;
    cin >> n >> q;
    for (long long i = 0; i <= n; i++)
      DP[i] = -1;
    for (long long i = 0; i < n; i++) {
      long long d, s;
      cin >> d >> s;
      dis.push_back(d);
      sp.push_back(s);
    }

    for (long long i = 0; i < n; i++) {
      for (long long j = 0; j < n; j++) {

        long long x;
        cin >> x;
        if (j - i == 1) {
          a[i] = x;
        }
      }
    }
    long long u, v;
    cin >> u >> v;

    DP[0] = 0;
    for (long long i = 0; i < n; i++) {
      long long di = a[i];
      for (long long j = i + 1; j < n; j++) {
        if (di > dis[i])
          break;
        double ans = DP[i] + ((double)di) / sp[i];
        if (DP[j] < 0) {
          DP[j] = ans;
          di += a[j];
          continue;
        }
        DP[j] = min(DP[j], ans);
        di += a[j];
      }
    }
    cout << setprecision(10) << fixed << "Case #" << cc << ": " << DP[n - 1]
         << endl;
    cc++;
  }
}
