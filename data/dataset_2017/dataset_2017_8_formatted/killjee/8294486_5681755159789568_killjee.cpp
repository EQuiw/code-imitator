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

vector<int> dis, sp;
double DP[155];
int a[155];

ll main() {
  freopen("Task.in", "r", stdin);
  freopen("Task.out", "w", stdout);
  int t, cc = 1;
  cin >> t;

  while (t--) {
    dis.clear();
    sp.clear();
    int n, q;
    cin >> n >> q;
    for (int i = 0; i <= n; i++)
      DP[i] = -1;
    for (int i = 0; i < n; i++) {
      int d, s;
      cin >> d >> s;
      dis.pb(d);
      sp.pb(s);
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {

        int x;
        cin >> x;
        if (j - i == 1) {
          a[i] = x;
        }
      }
    }
    int u, v;
    cin >> u >> v;

    DP[0] = 0;
    for (int i = 0; i < n; i++) {
      int di = a[i];
      for (int j = i + 1; j < n; j++) {
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