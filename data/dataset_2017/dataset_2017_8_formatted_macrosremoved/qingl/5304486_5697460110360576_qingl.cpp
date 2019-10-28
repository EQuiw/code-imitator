#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 105;
struct P {
  int l, r;
} d[N][N];
bool cmp(P x, P y) { return x.r < y.r; }
double a[N];
int tmp[N], pos[N];
bool u[N][N];
int main() {
  freopen("B-small-attempt2.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  int T, ca = 1;
  scanf("%d", &T);
  while (T--) {
    printf("Case #%d: ", ca++);
    int m, n;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
      scanf("%lf", &a[i]);
    }
    int e = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int x;
        scanf("%d", &x);
        int k = x / a[i], mi = -1, mx = -1;
        for (int h = 1; h <= 1200000; h++) {
          double ld = h * a[i] * 0.9;
          double rd = h * a[i] * 1.1;
          if (ld <= x && x <= rd) {
            if (mi == -1)
              mi = h;
            mx = h;
          }
          if (x < ld)
            break;
        }
        if (mi != -1) {
          d[i][j].l = mi;
          d[i][j].r = mx;
          tmp[e++] = mi;
        } else
          d[i][j].l = d[i][j].r = -1;
      }
    }
    for (int i = 0; i < n; i++)
      sort(d[i], d[i] + m, cmp);
    sort(tmp, tmp + e);
    /*for(int i=0;i<e;i++)printf("i:%d tmp:%d \n",i,tmp[i]);
    for(int i=0;i<n;i++)
    {
            for(int j=0;j<m;j++)printf("l:%d r:%d | ",d[i][j].l,d[i][j].r);
            puts("");
    }*/
    memset(u, 0, sizeof(u));
    int ret = 0;
    for (int i = 0; i < e; i++) {
      int x = tmp[i], f = 0;
      for (int j = 0; j < n; j++) {
        int ps = -1;
        for (int h = 0; h < m; h++)
          if (!u[j][h] && d[j][h].l != -1) {
            if (d[j][h].l <= x && d[j][h].r >= x) {
              ps = h;
              break;
            }
          }
        if (ps == -1) {
          f = 1;
          break;
        }
        pos[j] = ps;
      }
      if (!f) {
        for (int j = 0; j < n; j++) {
          u[j][pos[j]] = true;
        }
        ret++;
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}
