#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
// freopen("", "r", stdin);
// freopen("", "w", stdout);
// printf("Case #%d: ", ii);

int n, m;
int num[55];
int q[55][55];
int ans;
int vis[55];

void dfs(int x, int cnt) {
  ans = max(ans, cnt);
  for (int i = x; i <= m; i++) {
    int top = q[1][i] * 10.0 / (9.0 * num[1]),
        down = ceil(q[1][i] * 10.0 / (11.0 * num[1])) + 0.1;
    if (down > top) {
      continue;
    }
    for (int j = 1; j <= m; j++) {
      if (vis[j])
        continue;
      int top1 = q[2][j] * 10.0 / (0.9 * num[2]),
          down1 = ceil(q[2][j] * 10.0 / (11.0 * num[2])) + 0.1;
      if (down1 > top1) {
        continue;
      }
      int x = max(down, down1), y = min(top, top1);
      if (x <= y) {
        vis[j] = 1;
        dfs(i + 1, cnt + 1);
        vis[j] = 0;
      }
    }
  }
}

int main() {
  freopen("B-small-attempt1.in", "r", stdin);
  freopen("B-small-attempt1.out", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int ii = 1; ii <= T; ii++) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &num[i]);
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        scanf("%d", &q[i][j]);
      }
    }
    ans = 0;
    if (n == 1) {
      for (int i = 1; i <= m; i++) {
        int top = q[1][i] * 10.0 / (9.0 * num[1]),
            down = ceil(q[1][i] * 10.0 / (11.0 * num[1])) + 0.1;
        if (down > top) {
          continue;
        }
        ans++;
      }
    } else if (n == 2) {
      for (int i = 1; i <= m; i++) {
        int top = q[1][i] * 10.0 / (9.0 * num[1]),
            down = ceil(q[1][i] * 10.0 / (11.0 * num[1])) + 0.1;
        if (down > top) {
          continue;
        }
        for (int j = 1; j <= m; j++) {
          int top1 = q[2][j] * 10.0 / (9.0 * num[2]),
              down1 = ceil(q[2][j] * 10.0 / (11.0 * num[2])) + 0.1;
          if (down1 > top1) {
            continue;
          }
          int x = max(down, down1), y = min(top, top1);
          if (x <= y) {
            vis[j] = 1;
            dfs(i + 1, 1);
            vis[j] = 0;
          }
        }
      }
    }
    printf("Case #%d: %d\n", ii, ans);
  }
  return 0;
}
