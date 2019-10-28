#include <cstdio>
using namespace std;
int r, c;
char G[30][30];
bool allques[30], flag;
inline void solve() {
  scanf("%d%d", &r, &c);
  flag = true;
  allques[0] = false;
  for (int i = 1; i <= r; i++) {
    allques[i] = true;
    for (int j = 1; j <= c; j++) {
      scanf(" %c ", &G[i][j]);
      if (G[i][j] != '?')
        allques[i] = false;
    }
    if (!allques[i] && flag) {
      flag = false;
      for (int j = 1; j <= c; j++)
        G[0][j] = G[i][j];
    }
  }
  for (int i = 0; i <= r; i++) {
    if (allques[i]) {
      for (int j = 1; j <= c; j++)
        G[i][j] = G[i - 1][j];
    } else {
      for (int j = 1; j <= c; j++)
        if (G[i][j] != '?') {
          int k = j - 1;
          while (k >= 1 && G[i][k] == '?')
            G[i][k--] = G[i][j];
          k = j + 1;
          while (k <= c && G[i][k] == '?')
            G[i][k++] = G[i][j];
        }
    }
  }
  for (int i = 1; i <= r; i++) {
    for (int j = 1; j <= c; j++)
      printf("%c", G[i][j]);
    printf("\n");
  }
}
int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int i = 1; i <= T; i++) {
    printf("Case #%d:\n", i);
    solve();
  }
  return 0;
}
