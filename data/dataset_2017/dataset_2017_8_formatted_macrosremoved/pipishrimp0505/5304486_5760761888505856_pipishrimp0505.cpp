#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int R, C, cnt;
char ch[30][30], ans[30][30], c[30];
bool flag[200], vis;

bool Judge() {
  /*for(int j = 1; j <= R; j++) {
      for(int k = 1; k <= C; k++)
          printf("%c", ans[j][k]);
      printf("\n");
  }
  printf("\n");*/
  for (int i = 1; i <= cnt; i++) {
    int x1 = 0x3fffffff, y1 = 0x3fffffff, x2 = 0, y2 = 0;
    for (int j = 1; j <= R; j++)
      for (int k = 1; k <= C; k++)
        if (ans[j][k] == c[i]) {
          if (x1 == 0x3fffffff) {
            x1 = j, y1 = k;
          }
          x2 = j, y2 = k;
        }
    // if(num < (x2-x1+1)*(y2-y1+1)) return false;
    for (int j = 1; j <= R; j++)
      for (int k = 1; k <= C; k++) {
        if (j >= x1 && j <= x2 && k >= y1 && k <= y2) {
          if (ans[j][k] != c[i])
            return false;
        } else {
          if (ans[j][k] == c[i])
            return false;
        }
      }
    // printf("%d %d %d %d\n", x1, y1, x2, y2);
  }
  // printf("--------------\n");
  return true;
}

void dfs(int x, int y) {
  if (x > R) {
    if (Judge()) {
      for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++)
          printf("%c", ans[i][j]);
        printf("\n");
      }
      vis = true;
    }
    return;
  }
  if (ch[x][y] != '?') {
    ans[x][y] = ch[x][y];
    if (y == C)
      dfs(x + 1, 1);
    else
      dfs(x, y + 1);
  } else {
    for (int i = 1; i <= cnt && !vis; i++) {
      ans[x][y] = c[i];
      if (y == C)
        dfs(x + 1, 1);
      else
        dfs(x, y + 1);
    }
  }
}

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int T, num = 0;
  scanf("%d", &T);
  while (T--) {
    vis = false, cnt = 0;
    memset(flag, false, sizeof(flag));
    scanf("%d%d", &R, &C);
    for (int i = 1; i <= R; i++) {
      scanf("%s", ch[i] + 1);
      for (int j = 1; j <= C; j++)
        if (!flag[ch[i][j]] && ch[i][j] != '?') {
          flag[ch[i][j]] = true;
          c[++cnt] = ch[i][j];
        }
    }
    // for(int i = 1; i <= cnt; i++) printf("%c\n", c[i]);
    printf("Case #%d:\n", ++num);
    dfs(1, 1);
  }
}
