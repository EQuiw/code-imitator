#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

ld d[105];
ld e[105], v[105];
bool vis[105];
ld DP[105];
int n;
ld dp(int i) {
  if (vis[i])
    return DP[i];
  if (i == n)
    return 0;
  ld ans = 1e12;
  ld tot = 0;
  for (int k = i + 1; k <= n; k++) {
    tot += d[k - 1];
    if (tot > e[i])
      break;
    ans = min(ans, dp(k) + tot / v[i]);
  }
  vis[i] = true;
  return DP[i] = ans;
}
int main() {
  ios::sync_with_stdio(0);
  freopen("readable.txt", "w", stdout);
  int t;
  cin >> t;
  for (int ca = 1; ca <= t; ca++) {
    memset(vis, 0, sizeof vis);
    cin >> n;
    int q;
    cin >> q;
    for (int i = 1; i <= n; i++)
      cin >> e[i] >> v[i];
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        ld x;
        cin >> x;
        if (j == i + 1)
          d[i] = x;
      }
    }
    int x, y;
    cin >> x >> y;
    cout << "Case #" << ca << ": " << fixed << setprecision(10) << dp(1)
         << endl;
  }
  return 0;
}

// g++ -std=c++11 -O2 -Wfatal-errors -Im -Wall -Wextra -o "output.txt"
// "code.cpp"
