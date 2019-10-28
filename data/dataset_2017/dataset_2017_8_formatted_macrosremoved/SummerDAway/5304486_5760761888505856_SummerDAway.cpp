#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

int n, m;
char a[30][30];

void work() {
  scanf("%d%d", &n, &m);
  memset(a, 0, sizeof(a));
  for (int i = 0; i < n; ++i) {
    scanf("%s", a[i]);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (a[i][j] == '?') {
        if (j > 0 && a[i][j - 1] != '?') {
          a[i][j] = a[i][j - 1];
          continue;
        }
        int k = j;
        for (; j < m && a[i][j] == '?'; ++j)
          ;
        if (j < m) {
          for (; k < j; ++k)
            a[i][k] = a[i][j];
        }
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    if (a[i][0] == '?') {
      if (i > 0) {
        memcpy(a[i], a[i - 1], sizeof(a[i]));
      } else {
        int k = i;
        for (; i < n && a[i][0] == '?'; ++i)
          ;
        if (i < n) {
          for (; k < i; ++k)
            memcpy(a[k], a[i], sizeof(a[i]));
        }
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    printf("%s\n", a[i]);
  }
}

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int TC;
  scanf("%d", &TC);
  for (int tc = 1; tc <= TC; ++tc) {
    printf("Case #%d:\n", tc);
    work();
  }
}
