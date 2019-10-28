// satyaki3794
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define MOD (1000000007LL)
#define LEFT(n) (2 * (n))
#define RIGHT(n) (2 * (n) + 1)

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

ll pwr(ll base, ll p, ll mod = MOD) {
  ll ans = 1;
  while (p) {
    if (p & 1)
      ans = (ans * base) % mod;
    base = (base * base) % mod;
    p /= 2;
  }
  return ans;
}

ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int n, p, arr[55][55], req[55], DP[10][1024];

int dp(int i, int mask) {
  if (i == p)
    return 0;
  int &ans = DP[i][mask];
  if (ans != -1)
    return ans;
  ans = dp(i + 1, mask);
  for (int j = 0; j < p; j++) {
    if ((mask >> j) & 1)
      continue;
    int z = arr[0][i] / req[0];
    for (int x = z + 5; x >= z - 5 && x >= 1; x--) {
      int lo1 = ceil(1LL * x * req[0] * 0.9),
          hi1 = floor(1LL * x * req[0] * 1.1);
      int lo2 = ceil(1LL * x * req[1] * 0.9),
          hi2 = floor(1LL * x * req[1] * 1.1);
      if (arr[0][i] >= lo1 && arr[0][i] <= hi1 && arr[1][j] >= lo2 &&
          arr[1][j] <= hi2)
        ans = max(ans, 1 + dp(i + 1, mask | (1 << j)));
    }
  }
  // cout<<"dp "<<i<<" "<<mask<<" returns "<<ans<<endl;
  return ans;
}

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);

  freopen("B-small-attempt2.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t, x = 1;
  cin >> t;
  // t=1;
  while (t--) {

    cin >> n >> p;
    for (int i = 0; i < n; i++)
      cin >> req[i];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < p; j++)
        cin >> arr[i][j];

    if (n == 1) {
      int ans = 0;
      for (int i = 0; i < p; i++) {
        bool ok = false;
        for (int x = 2000000; x >= 1; x--) {
          int lo = ceil(1LL * x * req[0] * 0.9),
              hi = floor(1LL * x * req[0] * 1.1);
          if (arr[0][i] >= lo && arr[0][i] <= hi) {
            ok = true;
            break;
          }
        }
        ans += ok;
      }

      cout << "Case #" << x++ << ": " << ans << endl;
      continue;
    }

    memset(DP, -1, sizeof(DP));
    cout << "Case #" << x++ << ": " << dp(0, 0) << endl;
  }

  return 0;
}
