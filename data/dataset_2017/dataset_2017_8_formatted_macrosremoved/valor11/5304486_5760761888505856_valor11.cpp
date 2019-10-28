#include <bits/stdc++.h>
const int N = 26;
char s[N][N];
int n, m;
int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; cas++) {
    scanf("%d%d", &n, &m);
    bool flg = false;
    for (int i = 0; i < n; i++) {
      scanf("%s", s[i]);
      char sss = '?';
      for (int j = 0; j < m; j++)
        if (s[i][j] != '?') {
          sss = s[i][j];
          break;
        }
      if (sss == '?') {
        continue;
      }
      for (int j = 0; j < m; j++) {
        if (s[i][j] == '?')
          s[i][j] = sss;
        sss = s[i][j];
      }
    }

    for (int j = 0; j < m; j++) {
      char sss = '?';
      for (int i = 0; i < n; i++)
        if (s[i][j] != '?') {
          sss = s[i][j];
          break;
        }
      if (sss == '?') {
        flg = true;
        continue;
      }
      for (int i = 0; i < n; i++) {
        if (s[i][j] == '?')
          s[i][j] = sss;
        sss = s[i][j];
      }
    }

    if (flg) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          if (s[i][j] == '?')
            s[i][j] = 'A';
        }
      }
    }
    printf("Case #%d:\n", cas);
    for (int i = 0; i < n; i++)
      puts(s[i]);
  }
}
