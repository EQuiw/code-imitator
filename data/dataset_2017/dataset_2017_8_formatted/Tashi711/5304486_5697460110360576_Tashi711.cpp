#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int N = 100;

int n, m;

int a[N];
int u[N][N], v[N][N];
int ans;
bool vst[N][N];
int max_ans;

int dfs(int p, int i, int cur, int l, int r) {
  if (p == m + 1) {
    ans = max(ans, cur);
    if (ans == max_ans) {
      return 1;
    }
    return 0;
  }
  if (i == n + 1) {
    int res = dfs(p + 1, 1, cur + 1, -1, -1);
    return res;
  }
  if (i == 1) {
    int res = 0;
    if (u[1][p] <= v[1][p]) {
      res = dfs(p, i + 1, cur, u[1][p], v[1][p]);
      if (res) {
        return 1;
      }
    }
    if (m - p + cur > ans) {
      res = dfs(p + 1, 1, cur, -1, -1);
    }
    return res;
  }
  for (int j = 1; j <= m; ++j) {
    if (!vst[i][j]) {
      int uu = max(u[i][j], l);
      int vv = min(v[i][j], r);
      if (uu <= vv) {
        vst[i][j] = true;
        int res = dfs(p, i + 1, cur, uu, vv);
        if (res == 1) {
          return 1;
        }
        vst[i][j] = false;
      }
    }
  }
  return 0;
}

int calc(int k, int p) {
  for (int i = 1; i <= 4; ++i) {
    if (k >= 0.9 * p * i && k <= 1.1 * p * i) {
      return i;
    }
  }
  return -1;
}

void work() {
  memset(vst, 0, sizeof vst);
  ans = 0;
  cin >> n >> m;
  max_ans = m;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int w, i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &w);
      u[i][j] = (int)ceil(w / 1.1 / a[i]);
      v[i][j] = (int)floor(w / 0.9 / a[i]);
      if (u[i][j] < 5) {
        u[i][j] = v[i][j] = calc(w, a[i]);
        if (u[i][j] == -1) {
          u[i][j] = 0;
        }
      }
    }
  }
  dfs(1, 1, 0, -1, -1);
  cout << ans << endl;
}

int main() {
  freopen("my.in", "r", stdin);
  freopen("out.txt", "w", stdout);

  int q;
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    printf("Case #%d: ", i);
    work();
  }
  return 0;
}
