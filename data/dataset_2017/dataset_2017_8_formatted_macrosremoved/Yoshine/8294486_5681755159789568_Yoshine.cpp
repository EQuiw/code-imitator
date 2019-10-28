#include <bits/stdc++.h>
using namespace std;

long long s[123];
int d[123];

int t, n, qq, u, k;
int e[123], v[123];

vector<pair<int, long double>> g[123];
queue<int> q;
long double f[123];
bool vis[123];

void work(int ca) {
  scanf("%d %d", &n, &qq);
  for (int i = 1; i <= n; i++)
    scanf("%d %d", &e[i], &v[i]);
  int r;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      scanf("%d", &r);
      if (i + 1 == j)
        d[j] = r;
    }
  scanf("%d %d", &u, &k);
  s[0] = 0;
  d[0] = 0;
  d[1] = 0;
  for (int i = 1; i <= n; i++)
    s[i] = s[i - 1] + d[i];
  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j <= n; j++)
      if (s[j] - s[i] <= e[i]) {
        g[i].push_back(
            make_pair(j, (long double)(s[j] - s[i]) / (long double)v[i]));
      }
  }
  while (!q.empty())
    q.pop();
  for (int i = 1; i <= n; i++)
    f[i] = 1e13;
  q.push(1);
  vis[1] = 1;
  f[1] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = 0;
    for (int k = 0; k < g[u].size(); k++) {
      int v = g[u][k].first;
      double w = g[u][k].second;
      // cout << u << ' ' << v <<' ' <<w <<endl;
      if (f[v] > f[u] + w) {
        f[v] = f[u] + w;
        // cout << u << ' ' << v << ' ' << f[v] << endl;
        if (!vis[v]) {
          q.push(v);
          vis[v] = 1;
        }
      }
    }
  }
  printf("Case #%d: %.7lf\n", ca, (double)f[n]);
  for (int i = 1; i <= n; i++)
    g[i].clear();
}

int main() {
  cin >> t;
  for (int _ = 1; _ <= t; _++)
    work(_);
  return 0;
}
