#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define re(i, a, b) for (int i = a; i <= b; i++)
#define rep(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
int T;
int n, p;
int r[100];
int q[100][100], minq[100][100], maxq[100][100], flag[100];
int mark, tmin[100], tmax[100], last[100];
int top, ans;
int themin(int a, int b) {
  if (a < b)
    return a;
  return b;
}
int themax(int a, int b) {
  if (a > b)
    return a;
  return b;
}
int dfs(int k) {
  if (k == 0) {
    tmin[k] = minq[0][flag[k]];
    tmax[k] = maxq[0][flag[k]];
  } else {
    tmin[k] = themax(minq[k][flag[k]], tmin[k - 1]);
    tmax[k] = themin(maxq[k][flag[k]], tmax[k - 1]);
  }
  if (k == n - 1) {
    if (k > 0) {
      if (tmin[k] <= tmax[k]) {
        ans++;
        re(i, 0, n - 1) last[i] = flag[i];
        return 1;
      }
      return 0;
    }
    if (k == 0) {
      re(i, 0, p - 1) if (minq[0][i] <= maxq[0][i]) ans++;
      return 1;
    }
  }
  int mark = 0;
  while (1) {
    if (tmin[k] <= tmax[k])
      re(j, last[k + 1] + 1, p - 1) if (minq[k + 1][j] <= maxq[k + 1][j] &&
                                        !(minq[k + 1][j] > tmax[k] ||
                                          maxq[k + 1][j] < tmin[k])) // satisfy
      {
        flag[k + 1] = j;
        if (dfs(k + 1)) {
          mark = 1;
          break;
        }
      }
    flag[k]++;
    if (flag[k] == p)
      break;
    if (k == 0) {
      tmin[k] = minq[0][flag[k]];
      tmax[k] = maxq[0][flag[k]];
    } else {
      tmin[k] = themax(minq[k][flag[k]], tmin[k - 1]);
      tmax[k] = themin(maxq[k][flag[k]], tmax[k - 1]);
    }
  }
  return mark;
}
int main() {
  //	freopen("B.in","r",stdin);	freopen("B.out","w",stdout);
  scanf("%d", &T);
  re(casen, 1, T) {
    scanf("%d%d", &n, &p);
    re(i, 0, n - 1) scanf("%d", &r[i]);
    re(i, 0, n - 1) {
      re(j, 0, p - 1) scanf("%d", &q[i][j]);
      sort(q[i], q[i] + p);
    }
    re(i, 0, n - 1) re(j, 0, p - 1) {
      minq[i][j] = int(ceil(float(q[i][j]) * 10 / float(r[i]) / 11));
      while ((minq[i][j] - 1) * r[i] * 9 <= q[i][j] * 10 &&
             (minq[i][j] - 1) * r[i] * 11 >= q[i][j] * 10)
        minq[i][j]--;
      maxq[i][j] = int(float(q[i][j]) * 10 / float(r[i]) / 9);
      while ((maxq[i][j] + 1) * r[i] * 9 <= q[i][j] * 10 &&
             (maxq[i][j] + 1) * r[i] * 11 >= q[i][j] * 10)
        maxq[i][j]++;
    }
    ans = 0;
    memset(flag, 0, sizeof(flag));
    re(i, 0, n - 1) last[i] = -1;
    dfs(0);

    printf("Case #%d: %d\n", casen, ans);
  }
  //	fclose(stdin);fclose(stdout);
  return 0;
}
