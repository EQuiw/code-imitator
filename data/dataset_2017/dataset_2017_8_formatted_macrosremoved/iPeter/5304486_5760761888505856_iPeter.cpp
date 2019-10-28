#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int n, m;
char s[50][50];
int main(void) {
  int t;
  scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
      scanf("%s", s[i]);

    int ufx, ufy = 0;
    for (int i = 0; i < n; ++i) {
      ufx = 0;
      bool fill = false;
      for (int j = 0; j < m; ++j) {
        if (s[i][j] == '?')
          continue;
        fill = true;
        int st = ufx, ed = j + 1;
        for (; ed < m && s[i][ed] == '?'; ++ed)
          ;
        for (int x = st; x < ed; ++x)
          for (int y = ufy; y <= i; ++y)
            s[y][x] = s[i][j];
        ufx = ed;
      }
      if (fill)
        ufy = i + 1;
    }

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (s[i][j] == '?') {
          s[i][j] = s[i - 1][j];
        }

    printf("Case #%d:\n", tt);
    for (int i = 0; i < n; ++i)
      printf("%s\n", s[i]);
  }
  return 0;
}
