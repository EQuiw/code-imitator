#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int T, N;
int Q;

const int maxn = 105;

long long D[maxn][maxn];
double t[maxn][maxn];
long long E[maxn], S[maxn];

int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-small-attempt0.out", "w", stdout);
  int cas = 0;
  cin >> T;
  while (T--) {
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
      scanf("%lld%lld", &E[i], &S[i]);
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        int x;
        scanf("%d", &x);
        D[i][j] = x;
      }
    }
    for (int k = 1; k <= N; k++) {
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          if (D[i][k] >= 0 && D[k][j] >= 0 &&
              (D[i][j] < 0 || (D[i][k] + D[k][j] < D[i][j])))
            D[i][j] = D[i][k] + D[k][j];
        }
      }
    }

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        if (D[i][j] >= 0 && D[i][j] <= E[i])
          t[i][j] = D[i][j] / (1.0 * S[i]);
        else
          t[i][j] = -1;
      }
    }

    for (int k = 1; k <= N; k++) {
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          if (t[i][k] >= 0 && t[k][j] >= 0 &&
              (t[i][j] < 0 || (t[i][k] + t[k][j] < t[i][j])))
            t[i][j] = t[i][k] + t[k][j];
        }
      }
    }

    printf("Case #%d:", ++cas);
    for (int i = 1; i <= Q; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      printf(" %.10lf", t[u][v]);
    }
    puts("");
  }
  return 0;
}
