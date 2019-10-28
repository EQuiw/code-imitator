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
#define LL long long
#define eps 1e-8
#define mem(a, b) memset(a, b, sizeof(a))
#define zero(x) ((x > +eps) - (x < -eps))
#define MAX 100010
#define INF 100000000
#define MAXEDGE 50010
#define MAX 2100
using namespace std;
// freopen("", "r", stdin);
// freopen("", "w", stdout);
// printf("Case #%d: ", ii);

struct NODE {
  LL d, s;
} nodes[110];

int n, q;
LL mp[110][110];
LL dis[110];
int f[110][110];
double dp[110][110];

int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-small-attempt0.out", "w", stdout);
  int T;
  int a, b;
  scanf("%d", &T);
  for (int ii = 1; ii <= T; ii++) {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
      scanf("%lld%lld", &nodes[i].d, &nodes[i].s);
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        scanf("%lld", &mp[i][j]);
      }
    }
    dis[1] = 0;
    for (int i = 2; i <= n; i++) {
      dis[i] = dis[i - 1] + mp[i - 1][i];
    }
    while (q--) {
      scanf("%d%d", &a, &b);
      mem(f, -1);
      dp[1][1] = 0;
      f[1][1] = 0;
      for (int i = 2; i <= n; i++) {
        double min1 = 1000000000000000.0;
        int flag = 0;
        for (int j = 1; j < i; j++) {
          if (f[i - 1][j] != -1 && nodes[j].d >= dis[i] - dis[j]) {
            dp[i][j] = dp[j][j] + (dis[i] - dis[j]) * 1.0 / nodes[j].s;
            f[i][j] = 0;
            min1 = min(min1, dp[i][j]);
            flag = 1;
          }
        }
        if (flag) {
          dp[i][i] = min1;
          f[i][i] = 0;
        }
      }
      double ans = 100000000000.0;
      int vis = 0;
      for (int i = 1; i <= n; i++) {
        if (f[n][i] != -1) {
          vis = 1;
          ans = min(ans, dp[n][i]);
        }
      }
      printf("Case #%d: %.10lf\n", ii, ans);
    }
  }
  return 0;
}