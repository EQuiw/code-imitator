#include <bits/stdc++.h>
using namespace std;
#define mp(X, Y) make_pair(X, Y)
#define F first
#define S second
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;

int e[110], s[110];
int D[110][110];
vector<PII> G[110];
bool vis[110];
long double dp[110][110];
int main() {
  ios::sync_with_stdio(0);
  freopen("3.in", "r", stdin);
  freopen("3.out", "w", stdout);
  int cas = 1;
  int t;
  cin >> t;
  while (t--) {
    cout << "Case #" << cas++ << ":";
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
      cin >> e[i] >> s[i];
      G[i].clear();
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> D[i][j];
        if (D[i][j] != -1) {
          G[i].push_back(mp(j, D[i][j]));
        }
        dp[i][j] = 1e14;
      }
    }
    for (int i = 0; i < n; i++) {
      queue<PII> q;
      for (int j = 0; j < n; j++) {
        vis[j] = 0;
      }
      vis[i] = 1;
      q.push(mp(e[i], i));
      dp[i][i] = 0;
      long double pv = s[i];
      while (!q.empty()) {
        PII p = q.front();
        int last = p.F;
        int u = p.S;
        q.pop();
        for (int j = 0; j < G[u].size(); j++) {
          int v = G[u][j].F;
          if (vis[v])
            continue;
          int dis = G[u][j].S;
          if (dis > last)
            continue;
          q.push(make_pair(last - dis, v));
          vis[v] = 1;
          dp[i][v] = min(dp[u][v], dp[i][u] + (long double)(dis) / pv);
        }
      }
      // cout <<endl;
      // for(int j = 0 ; j < n; j ++){
      //    cout << dp[i][j] << " ";
      //}
    }
    // cout <<endl;
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          dp[i][j] = min(dp[i][k] + dp[k][j], dp[i][j]);
        }
      }
    }
    int u, v;
    for (int i = 0; i < q; i++) {
      cin >> u >> v;
      u--;
      v--;
      cout << fixed << setprecision(10) << " " << dp[u][v];
    }
    cout << endl;
  }
  return 0;
}
