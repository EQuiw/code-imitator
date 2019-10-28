#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;

const int N = 110;
int dist[N][N];
int e[N], s[N];
int n;
double pd[N][N];
bool vis[N][N];

ll tdist[N][N];
bool vis2[N][N];

ll calc_tdist(int i, int j) {
  if (i == j)
    return 0;

  if (vis2[i][j] == true)
    return tdist[i][j];

  vis2[i][j] = true;
  return tdist[i][j] = dist[i][i + 1] + calc_tdist(i + 1, j);
}

const double oo = 1e20;

double solve(int pos, int horse) {
  ll traversed = calc_tdist(horse, pos);
  ll rem = (ll)e[horse] - traversed;

  if (rem < 0)
    return oo;

  if (pos == n)
    return 0.0;

  if (vis[pos][horse])
    return pd[pos][horse];

  vis[pos][horse] = true;

  pd[pos][horse] =
      min(1.0 * dist[pos][pos + 1] / s[horse] + solve(pos + 1, horse),
          1.0 * dist[pos][pos + 1] / s[pos] + solve(pos + 1, pos));
  return pd[pos][horse];
}

int main() {
  int t, casecnt = 1;
  cin >> t;

  while (t--) {
    int q;
    memset(vis, 0, sizeof(vis));
    memset(vis2, 0, sizeof(vis2));

    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
      cin >> e[i] >> s[i];
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> dist[i][j];
      }
    }

    int u1, v1;
    cin >> u1 >> v1;

    double ans = 1.0 * dist[1][2] / s[1] + solve(2, 1);
    printf("Case #%d: %lf\n", casecnt++, ans);
  }

  return 0;
}
