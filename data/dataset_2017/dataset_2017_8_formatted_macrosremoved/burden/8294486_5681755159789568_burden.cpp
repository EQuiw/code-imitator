#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const double DINF = (double)1e50;
const long long INF = (long long)1e18;
const int Maxn = 110;
int n, q, E[Maxn], S[Maxn], Q[Maxn * 100];
long long G[Maxn][Maxn];
double Time[Maxn][Maxn];
bool boo[Maxn];

void spfa(int st, double *Result) {
  for (int i = 1; i <= n; i++)
    Result[i] = DINF;

  Result[st] = 0;
  boo[st] = 1;
  Q[1] = st;
  for (int head = 1, tail = 1; head <= tail; head++) {
    int u = Q[head];
    boo[u] = 0;
    for (int i = 1; i <= n; i++) {
      if (G[u][i] > E[u])
        continue;
      double temp = (double)G[u][i] / S[u];
      if (temp + Result[u] < Result[i]) {
        Result[i] = temp + Result[u];
        if (!boo[i]) {
          boo[i] = true;
          tail++;
          Q[tail] = i;
        }
      }
    }
  }
}

int main() {
  // freopen("c.in","r",stdin);
  // freopen("c.out","w",stdout);
  int T, w = 0;
  for (scanf("%d", &T); T--;) {
    scanf("%d%d", &n, &q);
    printf("Case #%d: ", ++w);
    for (int i = 1; i <= n; i++)
      scanf("%d%d", &E[i], &S[i]);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        int x;
        scanf("%d", &x);
        G[i][j] = x;
        if (x == -1)
          G[i][j] = INF;
      }

    for (int k = 1; k <= n; k++)
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          G[i][j] = min(G[i][j], G[i][k] + G[k][j]);

    for (int i = 1; i <= n; i++)
      spfa(i, Time[i]);

    for (; q--;) {
      int st, ed;
      scanf("%d%d", &st, &ed);
      printf(" %.12lf", Time[st][ed]);
    }
    printf("\n");
  }
  return 0;
}
