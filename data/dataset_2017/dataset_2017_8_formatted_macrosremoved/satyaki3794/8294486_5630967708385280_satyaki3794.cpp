// satyaki3794
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

ll pwr(ll base, ll p, ll mod = (1000000007LL)) {
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

int n;
double D, dist[1005], speed[1005];

bool possible(double mid) {
  for (int i = 1; i <= n; i++) {
    if (speed[i] > mid)
      continue;
    double x = (dist[i] / speed[i]) / (1.0 / speed[i] - 1.0 / mid);
    if (x <= D)
      return false;
  }
  return true;
}

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);

  freopen("A-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t, x = 1;
  cin >> t;
  while (t--) {

    cin >> D >> n;
    for (int i = 1; i <= n; i++)
      cin >> dist[i] >> speed[i];

    double ans = 0, lo = 0, hi = 1e18 + 2;
    for (int iter = 0; iter < 100; iter++) {
      double mid = (lo + hi) / 2;
      if (possible(mid)) {
        ans = max(ans, mid);
        lo = mid;
      } else {
        hi = mid;
      }
    }

    cout << "Case #" << x++ << ": " << fixed << setprecision(7) << ans << endl;
  }

  return 0;
}
