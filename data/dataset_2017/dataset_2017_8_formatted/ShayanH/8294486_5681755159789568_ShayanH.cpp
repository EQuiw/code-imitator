#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define SQR(a) ((a) * (a))
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define CLR(x, a) memset(x, a, sizeof x)
#define VAL(x) #x << " = " << (x) << "   "
#define FOREACH(i, x)                                                          \
  for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
#define FOR(i, n) for (int i = 0; i < (n); i++)
#define X first
#define Y second

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const int MAXN = 1 * 1000 + 10;

int e[MAXN], s[MAXN];
int d[MAXN][MAXN];
int qx[MAXN], qy[MAXN];
double dp[MAXN];

int main() {
  ios::sync_with_stdio(false);

  int tt;
  cin >> tt;
  for (int tc = 1; tc <= tt; tc++) {
    cout << "Case #" << tc << ": ";

    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
      cin >> e[i] >> s[i];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        cin >> d[i][j];
    for (int i = 0; i < q; i++)
      cin >> qx[i] >> qy[i];

    dp[0] = 0;
    for (int i = 1; i < n; i++)
      dp[i] = 1e15;

    for (int i = 0; i < n; i++) {
      int cur = 0;
      for (int j = i + 1; j < n; j++) {
        cur += d[j - 1][j];
        if (cur > e[i])
          break;

        dp[j] = min(dp[j], dp[i] + (double)cur / (double)s[i]);
      }
    }
    cout << fixed << setprecision(6) << dp[n - 1] << endl;
  }
  return 0;
}
