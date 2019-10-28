#include <cstdio>
#include <cstring>
#include <iostream>
#define rep(i, l, r) for (int i = l; i <= r; ++i)
using namespace std;
char s[30][30];
int n, m;
void work(int x) {
  rep(j, 1, m) {
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
  rep(cas, 1, T) {
    cin >> n >> m;
    rep(i, 1, n) scanf("%s", s[i] + 1);
    int first = 0;
    rep(i, 1, n) {
      rep(j, 1, m) if (s[i][j] != '?') first = i;
      if (first)
        break;
    }
    work(first);
    for (int i = first - 1; i >= 1; --i)
      rep(j, 1, m) s[i][j] = s[i + 1][j];
    rep(i, first + 1, n) {
      bool flag = 0;
      rep(j, 1, m) if (s[i][j] != '?') flag = 1;
      if (flag)
        work(i);
      else
        rep(j, 1, m) s[i][j] = s[i - 1][j];
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
