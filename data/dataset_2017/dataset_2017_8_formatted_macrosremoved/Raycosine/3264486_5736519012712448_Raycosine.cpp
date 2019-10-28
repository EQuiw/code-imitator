#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
int T;
char ch;
int a[1010], b[1010], cnt;
int n, k, m;
int flag;
int main() {
  // freopen("A.in","r",stdin);
  // freopen("A.out","w",stdout);
  scanf("%d", &T);
  for (int casen = 1; casen <= T; casen++) {
    n = 0;
    m = 0;
    while (1) {
      ch = getchar();
      if (ch == ' ')
        break;
      while (ch != '+' && ch != '-')
        ch = getchar();
      a[n++] = (ch == '+') ? 1 : 0;
      if (!a[n - 1])
        m++;
    }
    scanf("%d", &k);
    printf("Case #%d: ", casen);
    if (!(k % 2) && (m % 2)) {
      printf("IMPOSSIBLE\n");
      continue;
    }
    cnt = 0;
    for (int i = 0; i <= n - k; i++)
      if (!a[i]) {
        cnt++;
        for (int j = i; j <= i + k - 1; j++)
          a[j] = !a[j];
      }
    flag = 0;
    for (int i = n - k + 1; i < n; i++)
      if (!a[i]) {
        printf("IMPOSSIBLE\n");
        flag = 1;
        break;
      }
    if (flag == 0)
      printf("%d\n", cnt);
  }
  //	fclose(stdin);
  //	fclose(stdout);
  return 0;
}
