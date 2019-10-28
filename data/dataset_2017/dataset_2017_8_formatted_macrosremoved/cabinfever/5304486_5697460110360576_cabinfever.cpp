#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-6;

int T;
int n, p;
int r[60];
int c[60][60];
int ans = 0;
bool vis[60];
int f[60];

int check() {
  int ret = 0;
  for (int i = 1; i <= p; i++) {
    double k1 = (double)c[1][i] / r[1] / 1.1;
    double k2 = (double)c[1][i] / r[1] / 0.9;
    double k3 = (double)c[2][f[i]] / r[2] / 1.1;
    double k4 = (double)c[2][f[i]] / r[2] / 0.9;
    int k = c[1][i] / r[1];
    if ((k1 <= k && k2 >= k && k3 <= k && k4 >= k) ||
        (k1 <= k + 1 && k2 >= k + 1 && k3 <= k + 1 && k4 >= k + 1) ||
        (k1 <= k - 1 && k2 >= k - 1 && k3 <= k - 1 && k4 >= k - 1))
      ret++;
  }
  return ret;
}

void dfs(int x) {
  if (x == p + 1) {
    ans = max(ans, check());
    return;
  }
  for (int i = 1; i <= p; i++) {
    if (!vis[i]) {
      f[x] = i;
      vis[i] = 1;
      dfs(x + 1);
      vis[i] = false;
    }
  }
}

int main() {
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
  cin >> T;

  for (int ii = 1; ii <= T; ii++) {
    ans = 0;
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++)
      scanf("%d", &r[i]);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= p; j++)
        scanf("%d", &c[i][j]);
    if (n == 1) {
      for (int j = 1; j <= p; j++) {
        double k1 = (double)c[1][j] / r[1] / 1.1;
        double k2 = (double)c[1][j] / r[1] / 0.9;
        int k = c[1][j] / r[1];
        if ((k1 <= k && k2 >= k) || (k1 <= k + 1 && k2 >= k + 1) ||
            (k1 <= k - 1 && k2 >= k - 1))
          ans++;
      }
    } else
      dfs(1);
    printf("Case #%d: %d\n", ii, ans);
  }
  return 0;
}
