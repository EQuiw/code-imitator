#include <bits/stdc++.h>

using namespace std;

int query, n, p;
int r[1000];
int vmin[1000][1000], vmax[1000][1000];
int ans;
int xx[100];
bool mark[100];

const double EPS = (double)(1e-9);

bool check(int i, int j, int u, int v) {
  if (vmax[i][j] == -1 || vmax[u][v] == -1)
    return 0;
  if (vmax[i][j] >= vmin[u][v] && vmax[i][j] <= vmax[u][v])
    return 1;
  if (vmax[u][v] >= vmin[i][j] && vmax[u][v] <= vmax[i][j])
    return 1;
  return 0;
}

void tryy(int i) {
  if (i == p + 1) {
    int temp = 0;
    for (int j = 1; j <= p; j++)
      if (check(1, xx[j], 2, j))
        temp++;
    ans = max(ans, temp);
    return;
  }
  for (int j = 1; j <= p; ++j)
    if (!mark[j]) {
      mark[j] = 1;
      xx[i] = j;
      tryy(i + 1);
      mark[j] = 0;
    }
}

void solve1() {
  if (n == 1) {
    ans = 0;
    for (int i = 1; i <= p; i++)
      if (vmin[1][i] != -1)
        ans++;
    printf("%d\n", ans);
  } else if (n == 2) {
    ans = 0;
    tryy(1);
    printf("%d\n", ans);
  }
}

int getmin(int x, int y) {
  int mn = (int)(((double)((double)(10 * x) / 11.0)) + 0.5);
  if (mn == 0)
    return 0;
  mn -= 1;
  mn /= y;
  mn++;
  return mn;
}

int getmax(int x, int y) {
  int mn = (int)((10 * (double)x) / 9);
  return mn / y;
}

int main() {

  scanf("%d", &query);
  for (int t = 1; t <= query; ++t) {
    scanf("%d %d", &n, &p);
    for (int i = 1; i <= n; i++)
      scanf("%d", &r[i]);

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= p; ++j) {
        int x;
        scanf("%d", &x);
        vmin[i][j] = getmin(x, r[i]);
        vmax[i][j] = getmax(x, r[i]);
        if (vmin[i][j] > vmax[i][j])
          vmin[i][j] = vmax[i][j] = -1;
      }
    }

    printf("Case #%d: ", t);
    solve1();
  }
}