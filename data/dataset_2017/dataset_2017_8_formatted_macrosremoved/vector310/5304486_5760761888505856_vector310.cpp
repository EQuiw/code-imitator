#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
char s[30][30];
int n, m;
void work(int x) {
  for (int j = 1; j <= m; ++j) {
    if (s[x][j] != '?') {
      for (int k = j - 1; k >= 1 && s[x][k] == '?'; --k)
        s[x][k] = s[x][j];
      for (int k = j + 1; k <= m && s[x][k] == '?'; ++k)
        s[x][k] = s[x][j];
    }
  }
}
int main() {
  // freopen("input.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
  int T;
  cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
      scanf("%s", s[i] + 1);
    int first = 0;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j)
        if (s[i][j] != '?')
          first = i;
      if (first)
        break;
    }
    work(first);
    for (int i = first - 1; i >= 1; --i)
      for (int j = 1; j <= m; ++j)
        s[i][j] = s[i + 1][j];
    for (int i = first + 1; i <= n; ++i) {
      bool flag = 0;
      for (int j = 1; j <= m; ++j)
        if (s[i][j] != '?')
          flag = 1;
      if (flag)
        work(i);
      else
        for (int j = 1; j <= m; ++j)
          s[i][j] = s[i - 1][j];
    }
    printf("Case #%d:\n", cas);
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j)
        printf("%c", s[i][j]);
      printf("\n");
    }
  }
  return 0;
}
