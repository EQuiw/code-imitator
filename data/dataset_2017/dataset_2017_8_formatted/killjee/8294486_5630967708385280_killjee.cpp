#include <bits/stdc++.h>
using namespace std;

typedef int ll;

#define int long long
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define sz(x) ((int)x.size())
#define all(x) x.begin(), x.end()

typedef pair<int, int> pii;
typedef pair<int, pair<int, int>> piii;

const int mod = 1e9 + 7;

int POWER[65];
int power(int a, int b) {
  int ret = 1;
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
int inv(int x) { return power(x, mod - 2); }

void precompute() {
  POWER[0] = 1;
  for (int i = 1; i < 63; i++)
    POWER[i] = POWER[i - 1] << 1LL;
}

ll main() {
  freopen("Task.in", "r", stdin);
  freopen("Task.out", "w", stdout);
  int t, cc = 1;
  cin >> t;

  while (t--) {
    int d, n;
    cin >> d >> n;

    double tim = 0;
    for (int i = 0; i < n; i++) {
      int a, b;
      cin >> a >> b;
      double ti = (d - a) / ((double)b);
      tim = max(ti, tim);
    }
    cout << setprecision(10) << fixed << "Case #" << cc << ": " << d / tim
         << endl;
    cc++;
  }
}