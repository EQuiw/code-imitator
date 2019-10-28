#include <iostream>
#include <map>
#include <math.h>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;

double dist[110];
double speed[110];
double dp[110];
int g[110][110];
int src[110];
int dest[110];

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    double sum;
    int i, j, n, q;
    scanf("%d %d", &n, &q);
    for (i = 1; i <= n; i++) {
      scanf("%lf %lf", &dist[i], &speed[i]);
      dp[i] = 0x7f7f7f7f;
    }
    for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
        scanf("%d", &g[i][j]);
    for (i = 0; i < q; i++)
      scanf("%d %d", &src[i], &dest[i]);
    dp[1] = 0;
    for (i = 2; i <= n; i++) {
      sum = 0;
      for (j = i - 1; j > 0; j--) {
        sum += g[j][j + 1];
        if (sum > dist[j])
          continue;
        dp[i] = min(dp[i], dp[j] + sum / speed[j]);
      }
    }
    printf("Case #%d: %f\n", t, dp[n]);
  }
}
