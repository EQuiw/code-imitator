#include <bits/stdc++.h>

using namespace std;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define ld long double
#define ll long long
#define uint unsigned int
#define all(a) a.begin(), a.end()
#ifdef DEBUG
#define NAME "1"
#else
#define NAME "fox-blocks"
#endif
#define FREOPEN                                                                \
  freopen(NAME ".in", "r", stdin);                                             \
  freopen(NAME ".out", "w", stdout)
#define PI 3.1415926535897932384626433832795

const double EPS = 1e-9;
const double INF = 1e15;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  cout << fixed << setprecision(7);
  for (int qq = 1; qq <= t; ++qq) {
    cout << "Case #" << qq << ": ";
    int n, q;
    cin >> n >> q;
    ld e[n], s[n];
    for (int i = 0; i < n; ++i)
      cin >> e[i] >> s[i];
    ld g[n][n];
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        cin >> g[i][j];
        if (g[i][j] < 0)
          g[i][j] = INF;
      }
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          if (g[i][k] < INF && g[k][j] < INF)
            g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
    for (int c = 0; c < q; ++c) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      ld ans[n + 1];
      ans[u] = 0.0;
      for (int c = u + 1; c <= v; ++c) {
        ans[c] = INF;
        for (int j = c - 1; j >= u; --j) {
          if (e[j] >= g[j][c])
            ans[c] = min(ans[c], ans[j] + g[j][c] / s[j]);
        }
      }
      cout << ans[v] << " ";
    }
    cout << "\n";
  }
  return 0;
}