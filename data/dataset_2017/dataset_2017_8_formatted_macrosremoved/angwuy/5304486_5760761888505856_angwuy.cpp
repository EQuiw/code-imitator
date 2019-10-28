#include <cstdio>
#include <cstring>

const int MAXN = 30;

int n, m;
char a[MAXN][MAXN];

void init() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i)
    scanf("%s", a[i]);
}

void solve() {
  int l = -1;
  for (int i = 0; i < n; ++i) {
    char tmp = '?';
    for (int j = 0; j < m; ++j)
      if (a[i][j] != '?') {
        tmp = a[i][j];
        break;
      }
    if (tmp == '?')
      continue;
    else if (l == -1)
      l = i;
    for (int j = 0; j < m; ++j)
      if (a[i][j] == '?')
        a[i][j] = tmp;
      else
        tmp = a[i][j];
  }
  for (int i = 0; i < n; ++i) {
    if (a[i][0] == '?')
      printf("%s\n", a[l]);
    else {
      l = i;
      printf("%s\n", a[i]);
    }
  }
}

int main() {
  int tt;
  scanf("%d", &tt);
  for (int ii = 1; ii <= tt; ++ii) {
    init();
    printf("Case #%d:\n", ii);
    solve();
  }
  return 0;
}
