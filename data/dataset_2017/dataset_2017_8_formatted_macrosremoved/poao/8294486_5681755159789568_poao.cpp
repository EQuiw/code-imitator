#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

int T;

const int MN = 110;
int N, Q;
int U, V;

long long dst[MN][MN];
int E[MN], S[MN];
// bool pos[MN][MN];
// double dp[MN][MN];
double ans[MN];

int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-small-attempt0.out", "w", stdout);
  scanf("%d", &T);
  for (int tc = 1; tc <= T; tc++) {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++) {
      scanf("%d%d", &E[i], &S[i]);
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        scanf("%I64d", &dst[i][j]);
      }
    }
    for (int i = 0; i < Q; i++) {
      scanf("%d%d", &U, &V);
    }
    // warshall
    for (int k = 1; k <= N; k++) {
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          if (dst[i][k] == -1 || dst[k][j] == -1)
            continue;
          if (dst[i][j] == -1 || dst[i][j] > dst[i][k] + dst[k][j]) {
            dst[i][j] = dst[i][k] + dst[k][j];
          }
        }
      }
    }
    /*for(int i=0; i<=N; i++) {
            for(int j=0; j<=N; j++) {
                    pos[i][j] = false;
            }
    }*/
    // pos[1][1] = true;
    // dp[1][1] = 0.0f;
    ans[1] = 0.0f;
    for (int i = 2; i <= N; i++) {
      bool found = false;
      for (int j = 1; j < i; j++) {
        double now;
        if (E[j] >= dst[j][i]) {
          now = ans[j] + ((double)dst[j][i] / S[j]);
          if (!found || ans[i] > now) {
            ans[i] = now;
            found = true;
          }
        }
      }
      if (!found)
        fprintf(stderr, "WTFFFFFFF");
    }
    printf("Case #%d: %.7f\n", tc, ans[N]);
  }
  return 0;
}
