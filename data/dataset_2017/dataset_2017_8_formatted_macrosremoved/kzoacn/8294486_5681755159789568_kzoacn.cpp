#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
int n, q;
int e[maxn], s[maxn];
int d[maxn][maxn];
int dis[maxn];
void solve() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> e[i] >> s[i];
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> d[i][j];

  dis[1] = 0;
  for (int i = 2; i <= n; i++)
    dis[i] = dis[i - 1] + d[i - 1][i];

  /*	for(int i=1;i<=n;i++)
                  cerr<<dis[i]<<" ";
          cerr<<endl;
  */
  while (q--) {
    int u, v;
    cin >> u >> v;
    static double dp[maxn];
    for (int i = 1; i <= n; i++)
      dp[i] = 1e30;
    dp[1] = 0;
    for (int i = 1; i < n; i++) {
      int cur = 0;
      for (int j = i + 1; j <= n; j++) {
        if (e[i] < dis[j] - dis[i])
          break;
        //				cerr<<i<<" "<<j<<endl;
        int delta = dis[j] - dis[i];
        double t = 1.0 * delta / s[i];
        dp[j] = min(dp[j], dp[i] + t);
      }
    }
    printf("%.10f ", dp[n]);
  }
  puts("");
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cerr << t << endl;
    printf("Case #%d: ", t);
    solve();
  }
  return 0;
}
