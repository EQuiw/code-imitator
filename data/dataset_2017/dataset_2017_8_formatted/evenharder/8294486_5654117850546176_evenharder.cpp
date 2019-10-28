#include <algorithm>
#include <stdio.h>
#include <string.h>
#define _FILE_INPUT 0

void process(int TEST_CASE) {
  int n, r, o, y, g, b, v;
  int flag = 0;
  scanf("%d%d%d%d%d%d%d", &n, &r, &o, &y, &g, &b, &v);

  int a[1001];
  memset(a, -1, sizeof(a));
  int m = std::max(std::max(r, y), b);
  if (n / 2 < m)
    flag = 1;
  if (flag == 0) {
    int c;
    if (m == r)
      c = 0;
    else if (m == y)
      c = 1;
    else
      c = 2;
    int x[3] = {};
    x[0] = r;
    x[1] = y;
    x[2] = b;
    for (int i = 0; i < m; i++)
      a[2 * i] = c;

    for (int i = 0; i < n; i++) {
      if (a[i] == -1) {
        if (x[(c + 1) % 3] > x[(c + 2) % 3]) {
          a[i] = (c + 1) % 3;
          x[(c + 1) % 3]--;
        } else {
          a[i] = (c + 2) % 3;
          x[(c + 2) % 3]--;
        }
      }
    }
  }
  printf("Case #%d: ", TEST_CASE);
  if (flag)
    printf("IMPOSSIBLE");
  else {
    for (int i = 0; i < n; i++) {
      switch (a[i]) {
      case 0:
        printf("R");
        r--;
        break;
      case 1:
        printf("Y");
        y--;
        break;
      case 2:
        printf("B");
        b--;
        break;
      }
    }
  }
  puts("");
}

int main() {
#if _FILE_INPUT
  freopen(".in", "r", stdin);
  freopen(".out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    process(i);
  }

#if _FILE_INPUT
  fclose(stdin);
  fclose(stdout);
#endif
}