#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
int n, m;
char s[30][30];
bool flag;

int main() {
  // freopen("a.in","r",stdin);
  // freopen("a.out","w",stdout);
  int T, w = 0;
  for (scanf("%d", &T); T--;) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
      scanf("%s", s[i]);
    int j, temp = 0;
    for (int i = 0; i < n; i++) {
      flag = false;
      int p = 0;
      for (int j = 0; j < m; j++)
        if (s[i][j] != '?') {
          flag = true;
          for (int k = temp; k <= i; k++)
            for (int x = p; x <= j; x++)
              s[k][x] = s[i][j];
          p = j + 1;
        }
      if (p < m && flag) {
        for (int k = temp; k <= i; k++)
          for (int x = p; x < m; x++)
            s[k][x] = s[i][p - 1];
      }
      if (flag)
        temp = i + 1;
    }
    if (temp < n) {
      for (int k = temp; k < n; k++)
        for (int x = 0; x < m; x++)
          s[k][x] = s[temp - 1][x];
    }
    printf("Case #%d:\n", ++w);
    for (int i = 0; i < n; i++)
      printf("%s\n", s[i]);
  }
  return 0;
}
