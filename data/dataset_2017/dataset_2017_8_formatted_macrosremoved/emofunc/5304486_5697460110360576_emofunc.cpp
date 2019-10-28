#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;
const int N = 60;
int T_T;
struct node {
  int x, y;
  node(int _x = 0, int _y = 0) {
    x = _x;
    y = _y;
  }
  bool operator<(const node &t) const {
    return x < t.x || (x == t.x && y < t.y);
  }
} Q[N][N];
int n, p, a[N], value[N][N], ans;
int pos[N];
void work() {
  for (int i = 1; i <= n; i++)
    pos[i] = 1;
  int cur = 1;
  int flag = 1;
  while (flag) {
    for (int i = 1; i <= n; i++) {
      int q = pos[i];
      while (q <= p && Q[i][q].y < cur)
        q++;
      pos[i] = q;
      if (q > p) {
        flag = 0;
        break;
      }
    }
    if (!flag)
      break;
    int f = 1;
    for (int i = 1; i <= n; i++) {
      if (Q[i][pos[i]].x <= cur && Q[i][pos[i]].y >= cur)
        continue;
      else
        f = 0;
      break;
    }
    if (f) {
      ans++;
      for (int i = 1; i <= n; i++)
        pos[i]++;
    } else
      cur++;
  }
}
int main() {

  scanf("%d", &T_T);
  for (int cas = 1; cas <= T_T; cas++) {
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= p; j++)
        scanf("%d", &value[i][j]);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= p; j++) {
        int tmpx = floor(1.0 * value[i][j] / 0.9 / a[i]);
        int tmpy = ceil(1.0 * value[i][j] / 1.1 / a[i]);
        if (tmpy <= tmpx)
          Q[i][j] = node(tmpy, tmpx);
        else
          Q[i][j] = node(-1, -1);
      }
      sort(Q[i] + 1, Q[i] + 1 + p);
    }
    ans = 0;
    work();
    printf("Case #%d: %d\n", cas, ans);
  }
}
