
/*
Contest: Google Code Jam 2017 [Round 1B]
*/

#include <algorithm>
#include <stdio.h>
using namespace std;

int n, q;
double bat[1111];
double speed[1111];
double cumu[1111];

double dst[1111][1111];
double dp[1111];

double solve() {
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    int e, s;
    scanf("%d%d", &e, &s);
    bat[i] = e;
    speed[i] = s;
  }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      int d;
      scanf("%d", &d);
      dst[i][j] = d;
    }
  int t1, t2;
  scanf("%d%d", &t1, &t2); // Just Waste for SMALL
  cumu[0] = 0;
  for (int i = 0; i + 1 < n; i++)
    cumu[i + 1] = cumu[i] + dst[i][i + 1];
  for (int i = 0; i < n; i++)
    dp[i] = 999999999999999.999;
  // Calculate
  dp[n - 1] = 0;
  for (int i = n - 2; i >= 0; i--) {
    for (int j = i + 1; j < n; j++) {
      double togo = cumu[j] - cumu[i];
      if (togo > bat[i])
        break;
      double tu = togo / speed[i];
      dp[i] = min(dp[i], tu + dp[j]);
    }
  }
  return dp[0];
}

int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-Small.txt", "w", stdout);
  int tc;
  scanf("%d", &tc);
  for (int t = 1; t <= tc; t++) {
    printf("Case #%d: ", t);
    double ans = solve();
    printf("%.9f\n", ans);
  }
  return 0;
}
