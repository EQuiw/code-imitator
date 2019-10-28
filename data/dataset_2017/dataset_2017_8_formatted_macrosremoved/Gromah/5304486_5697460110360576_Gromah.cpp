#include <algorithm>
#include <cstdio>
using namespace std;

int Case, n, p, tot, S, T, R[50 + 5], Q[50 + 5][50 + 5], Num[50 + 5][50 + 5],
    Head[2500 + 5], Dfn[2500 + 5], q[2500 + 5];
int Max = 0;
bool Map[50 + 5][50 + 5], Flag[50 + 5];

struct Edge {
  int next, node, flow;
} h[1000000 + 5];

inline void addedge(int u, int v, int fl) {
  h[++tot].next = Head[u], Head[u] = tot;
  h[tot].node = v, h[tot].flow = fl;
  h[++tot].next = Head[v], Head[v] = tot;
  h[tot].node = u, h[tot].flow = 0;
}

bool Check(int u, int v) {
  if (n == 1) {
    for (int i = 1; i <= 1000000 && i * R[1] <= 100000000; i++) {
      bool ok_1 = Q[1][u] * 10 >= i * R[1] * 9 && Q[1][u] * 10 <= i * R[1] * 11;
      if (ok_1)
        return 1;
    }
  } else if (n == 2) {
    for (int i = 1;
         i <= 1000000 && i * R[1] <= 100000000 && i * R[2] <= 100000000; i++) {
      bool ok_1 = Q[1][u] * 10 >= i * R[1] * 9 && Q[1][u] * 10 <= i * R[1] * 11;
      bool ok_2 = Q[2][u] * 10 >= i * R[2] * 9 && Q[2][u] * 10 <= i * R[2] * 11;
      if (ok_1 && ok_2)
        return 1;
    }
  }
  return 0;
}

void dfs(int dep, int cur) {
  if (dep > p) {
    Max = max(Max, cur);
    return;
  }
  for (int i = 1; i <= p; i++)
    if (!Flag[i]) {
      Flag[i] = 1;
      dfs(dep + 1, cur + Map[dep][i]);
      Flag[i] = 0;
    }
}

int main() {
  scanf("%d", &Case);
  for (int Test = 1; Test <= Case; Test++) {
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++)
      scanf("%d", R + i);
    for (int i = 1, id = 0; i <= n; i++)
      for (int j = 1; j <= p; j++) {
        scanf("%d", Q[i] + j);
        Num[i][j] = ++id;
      }
    for (int i = 1; i <= p; i++)
      for (int j = 1; j <= p; j++)
        Map[i][j] = Check(i, j);
    Max = 0;
    dfs(1, 0);
    printf("Case #%d: %d\n", Test, Max);
  }
  return 0;
}
