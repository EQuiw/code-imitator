#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int T_T, n, m;
char str[30][30];
int main(void) {

  scanf("%d", &T_T);
  for (int cas = 1; cas <= T_T; cas++) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
      scanf("%s", str[i]);
    int last = 0, i, j, flag = 0;
    for (i = 0; i < n; i++) {
      flag = 0;
      int lastj = 0;
      for (j = 0; j < m; j++) {
        if (str[i][j] != '?') {
          //                    printf("i = %d, j = %d\n",i,j);
          flag = 1;
          for (int k = last; k <= i; k++)
            for (int l = lastj; l <= j; l++)
              str[k][l] = str[i][j];
          lastj = j + 1;
        }
      }
      if (flag && lastj < m) {
        for (int k = last; k <= i; k++)
          for (int l = lastj; l < m; l++)
            str[k][l] = str[i][lastj - 1];
      }
      if (flag)
        last = i + 1;
    }
    if (last < n) {
      for (int k = last; k < n; k++)
        for (int l = 0; l < m; l++)
          str[k][l] = str[last - 1][l];
    }
    printf("Case #%d:\n", cas);
    for (int i = 0; i < n; i++)
      printf("%s\n", str[i]);
  }
  return 0;
}
