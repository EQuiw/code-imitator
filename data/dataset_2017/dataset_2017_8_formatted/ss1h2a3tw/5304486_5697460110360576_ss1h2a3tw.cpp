#include <algorithm>
#include <cstdio>
using namespace std;

int n, p;
int r[60];
int q[60][60];
int minq[60][60];
int maxq[60][60];
bool used[60][60];

int nexthead() {
  for (int i = 0; i < p; i++) {
    if (used[0][i] == false)
      return i;
  }
  return p;
}
int dfs(int nown, int nowp, int nowmin, int nowmax) {
  nowmin = max(nowmin, minq[nown][nowp]);
  nowmax = min(nowmax, maxq[nown][nowp]);
  if (nowp == p)
    return 0;
  used[nown][nowp] = true;
  if (nown == n - 1) {
    int ans = 1;
    if (nowmin > nowmax)
      ans = 0;
    ans += dfs(0, nexthead(), 0, 10000000);
    used[nown][nowp] = false;
    return ans;
  }
  if (nowmin > nowmax) {
    used[nown][nowp] = false;
    return -1;
  }
  int ans = -1;
  for (int i = 0; i < p; i++) {
    if (used[nown + 1][i] != true) {
      ans = max(dfs(nown + 1, i, nowmin, nowmax), ans);
    }
  }
  if (ans == -1) {
    ans = dfs(0, nexthead(), 0, 10000000);
  }
  used[nown][nowp] = false;
  return ans;
}
int main() {
  int T;
  scanf("%d", &T);
  for (int I = 1; I <= T; I++) {
    fill((bool *)used, (bool *)used + 3600, false);
    scanf("%d%d", &n, &p);
    for (int i = 0; i < n; i++) {
      scanf("%d", r + i);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        scanf("%d", &(q[i][j]));
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        int tmp = q[i][j] * 10;
        int tmpr = r[i] * 9;
        maxq[i][j] = tmp / tmpr;
        tmpr = r[i] * 11;
        minq[i][j] = tmp / tmpr;
        if (tmp % tmpr != 0)
          minq[i][j]++;
      }
    }
    int ans = dfs(0, 0, 0, 10000000);
    if (ans == -1)
      ans = 0;
    printf("Case #%d: %d\n", I, ans);
  }
}
