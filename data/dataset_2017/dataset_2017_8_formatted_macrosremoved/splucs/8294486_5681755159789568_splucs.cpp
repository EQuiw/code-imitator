#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll dist[109][109], E[109], S[109];
int N;
double t[109][109];

void floydwarshall1() {
  for (int k = 1; k <= N; k++)
    for (int i = 1; i <= N; i++)
      for (int j = 1; j <= N; j++)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

void floydwarshall2() {
  for (int k = 1; k <= N; k++)
    for (int i = 1; i <= N; i++)
      for (int j = 1; j <= N; j++)
        t[i][j] = min(t[i][j], t[i][k] + t[k][j]);
}

int main() {
  int T, Q, U, V;
  scanf("%d", &T);
  for (int caseNo = 1; caseNo <= T; caseNo++) {
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; i++) {
      scanf("%I64d %I64d", &E[i], &S[i]);
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        scanf("%I64d", &dist[i][j]);
        if (dist[i][j] == -1)
          dist[i][j] = (1ll << 60);
      }
    }
    floydwarshall1();
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        if (dist[i][j] > E[i])
          t[i][j] = 1e+14;
        else
          t[i][j] = dist[i][j] * 1.0 / S[i];
      }
    }
    floydwarshall2();
    /*for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                    printf(" %.3f", t[i][j]);
            }
            printf("\n");
    }*/
    printf("Case #%d:", caseNo);
    while (Q--) {
      scanf("%d %d", &U, &V);
      printf(" %.7f", t[U][V]);
    }
    printf("\n");
  }
  return 0;
}
