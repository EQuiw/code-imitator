#include <bits/stdc++.h>
using namespace std;
const int N = 25 + 5;
int T, Case, n, m;
char s[N][N];
int ch[128][4], ex[128];

void dfsx(int c) {
  int can = 1;
  while (can) {
    can = 0;
    int x;
    x = ch[c][0] - 1;
    if (x >= 0) {
      int flag = 1;
      for (int i = ch[c][1]; i <= ch[c][3]; i++) {
        if (s[x][i] != '?')
          flag = 0;
      }
      if (flag) {
        for (int i = ch[c][1]; i <= ch[c][3]; i++) {
          s[x][i] = c;
        }
        can = 1;
        ch[c][0]--;
        continue;
      }
    }

    x = ch[c][2] + 1;
    if (x < n) {
      int flag = 1;
      for (int i = ch[c][1]; i <= ch[c][3]; i++) {
        if (s[x][i] != '?')
          flag = 0;
      }
      if (flag) {
        for (int i = ch[c][1]; i <= ch[c][3]; i++) {
          s[x][i] = c;
        }
        can = 1;
        ch[c][2]++;
        continue;
      }
    }
  }
}

void dfsy(int c) {
  int can = 1;
  while (can) {
    can = 0;
    int y;
    y = ch[c][1] - 1;
    if (y >= 0) {
      int flag = 1;
      for (int i = ch[c][0]; i <= ch[c][2]; i++) {
        if (s[i][y] != '?')
          flag = 0;
      }
      if (flag) {
        for (int i = ch[c][0]; i <= ch[c][2]; i++) {
          s[i][y] = c;
        }
        can = 1;
        ch[c][1]--;
        continue;
      }
    }

    y = ch[c][3] + 1;
    if (y < m) {
      int flag = 1;
      for (int i = ch[c][0]; i <= ch[c][2]; i++) {
        if (s[i][y] != '?')
          flag = 0;
      }
      if (flag) {
        for (int i = ch[c][0]; i <= ch[c][2]; i++) {
          s[i][y] = c;
        }
        can = 1;
        ch[c][3]++;
        continue;
      }
    }
  }
}

int main() {
  freopen("A-small-attempt2.in", "r", stdin);
  freopen("out2.out", "w", stdout);
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
      scanf("%s", s[i]);
    }
    memset(ex, 0, sizeof(ex));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (s[i][j] == '?')
          continue;
        int c = s[i][j];
        if (ex[c] == 0) {
          ex[c] = 1;
          ch[c][0] = ch[c][1] = 88888;
          ch[c][2] = ch[c][3] = 0;
        }
        ch[c][0] = min(ch[c][0], i);
        ch[c][1] = min(ch[c][1], j);
        ch[c][2] = max(ch[c][2], i);
        ch[c][3] = max(ch[c][3], j);
      }
    }
    for (int c = 'A'; c <= 'Z'; c++) {
      if (!ex[c])
        continue;
      for (int i = ch[c][0]; i <= ch[c][2]; i++) {
        for (int j = ch[c][1]; j <= ch[c][3]; j++) {
          s[i][j] = c;
        }
      }
    }
    for (int c = 'A'; c <= 'Z'; c++) {
      if (!ex[c])
        continue;
      dfsx(c);
    }
    for (int c = 'A'; c <= 'Z'; c++) {
      if (!ex[c])
        continue;
      dfsy(c);
    }
    printf("Case #%d:\n", ++Case);
    for (int i = 0; i < n; i++)
      puts(s[i]);
  }
  return 0;
}
