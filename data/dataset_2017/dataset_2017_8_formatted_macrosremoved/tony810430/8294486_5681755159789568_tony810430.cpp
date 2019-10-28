#include <algorithm>
#include <stdio.h>
using namespace std;

int T, cas;
int N, Q;
long long E[105];
int S[105];
long long D[105][105];
int U[105];
int V[105];
double dis[105][105];

void solve() {
  for (int k = 1; k <= N; k++) {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        if (D[i][k] == -1)
          continue;
        if (D[k][j] == -1)
          continue;
        if (D[i][j] == -1 || D[i][j] > D[i][k] + D[k][j])
          D[i][j] = D[i][k] + D[k][j];
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      if (D[i][j] <= E[i]) {
        dis[i][j] = double(D[i][j]) / S[i];
      } else {
        dis[i][j] = -1.0;
      }
    }
  }

  for (int k = 1; k <= N; k++) {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        if (dis[i][k] < 0.0)
          continue;
        if (dis[k][j] < 0.0)
          continue;
        if (dis[i][j] < 0.0 || dis[i][j] > dis[i][k] + dis[k][j])
          dis[i][j] = dis[i][k] + dis[k][j];
      }
    }
  }

  for (int i = 0; i < Q; i++) {
    printf(" %.6lf", dis[U[i]][V[i]]);
  }
}

int main() {
  scanf(" %d", &T);
  for (cas = 1; cas <= T; cas++) {
    scanf(" %d %d", &N, &Q);
    for (int i = 1; i <= N; i++) {
      scanf(" %lld %d", &E[i], &S[i]);
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        scanf(" %lld", &D[i][j]);
      }
    }
    for (int i = 0; i < Q; i++) {
      scanf(" %d %d", &U[i], &V[i]);
    }

    printf("Case #%d:", cas);
    solve();
    puts("");
  }

  return 0;
}
