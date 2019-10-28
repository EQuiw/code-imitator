#include <cstdio>
#include <cstring>
using namespace std;
int test, r, c, i, j, k, a[100];
char s[100][100];
bool used[100];
int main() {
  // freopen("a.in","r",stdin);
  // freopen("a.out","w",stdout);
  scanf("%d", &test);
  for (int kase = 1; kase <= test; kase++) {
    scanf("%d%d", &r, &c);
    for (i = 1; i <= r; i++)
      scanf("%s", s[i]);
    memset(used, 0, sizeof(used));
    for (i = 1; i <= r; i++) {
      char now = '?';
      for (j = 0; j < c; j++) {
        if (used[s[i][j] - 'A'])
          continue;
        if (s[i][j] == '?')
          s[i][j] = now;
        if (now != s[i][j])
          now = s[i][j];
      }
      if (s[i][c - 1] == '?') {
        continue;
      }

      for (j = c - 1; j >= 0; j--)
        if (s[i][j] == '?')
          s[i][j] = s[i][j + 1];
      if (i == r)
        continue;
      a[0] = 0;
      int num = 0;
      for (j = 1; j < c; j++)
        if (s[i][j] != s[i][j - 1])
          a[++num] = j;
      a[++num] = c;
      for (k = 0; k < num; k++) {
        used[s[i][a[k]] - 'A'] = 1;
        bool flag = 1;
        for (j = a[k]; j < a[k + 1]; j++)
          if (s[i + 1][j] != '?') {
            flag = 0;
            break;
          }
        if (flag)
          for (j = a[k]; j < a[k + 1]; j++)
            s[i + 1][j] = s[i][a[k]];
      }
      // printf("      %s\n",s[i]);
    }
    for (i = r; i >= 1; i--) {
      if (s[i][0] == '?') {
        // printf("111111111111\n");
        for (j = 0; j < c; j++)
          s[i][j] = s[i + 1][j];
      }
    }
    printf("Case #%d:\n", kase);
    for (i = 1; i <= r; i++) {
      printf("%s\n", s[i]);
    }
  }
  // fclose(stdin);fclose(stdout);
}
