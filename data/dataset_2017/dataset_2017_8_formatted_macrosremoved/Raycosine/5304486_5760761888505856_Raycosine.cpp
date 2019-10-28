#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;
int T, casen;
int r, c;
char a[100][100];
int mark[26];
char ch;
int k;
int main() {
  //	freopen("A.in","r",stdin);
  //	freopen("A.out","w",stdout);
  scanf("%d", &T);
  for (int casen = 1; casen <= T; casen++) {
    scanf("%d%d", &r, &c);
    memset(mark, 0, sizeof(mark));
    for (int i = 0; i <= r - 1; i++)
      for (int j = 0; j <= c - 1; j++) {
        ch = getchar();
        while ((ch < 'A' || ch > 'Z') && ch != '?')
          ch = getchar();
        a[i][j] = ch;
      }
    for (int i = 0; i <= r - 1; i++)
      for (int j = 0; j <= c - 1; j++)
        if (a[i][j] != '?') {
          k = j + 1;
          while (k < c && a[i][k] == '?') {
            a[i][k] = a[i][j];
            k++;
          }
        }
    for (int i = r - 1; i >= 0; i--)
      for (int j = c - 1; j >= 0; j--)
        if (a[i][j] != '?') {
          k = j - 1;
          while (k >= 0 && a[i][k] == '?') {
            a[i][k] = a[i][j];
            k--;
          }
        }
    for (int i = 0; i <= r - 1; i++)
      for (int j = 0; j <= c - 1; j++)
        if (a[i][j] == '?') {
          if (i == 0) {
            for (k = 0; k < c; k++)
              a[i][k] = a[i + 1][k];
            break;
          } else {
            for (k = 0; k < c; k++)
              a[i][k] = a[i - 1][k];
            break;
          }
        }

    for (int i = r - 1; i >= 0; i--)
      for (int j = 0; j <= c - 1; j++)
        if (a[i][j] == '?') {
          if (i == r - 1) {
            for (k = 0; k < c; k++)
              a[i][k] = a[i - 1][k];
            break;
          } else {
            for (k = 0; k < c; k++)
              a[i][k] = a[i + 1][k];
            break;
          }
        }
    printf("Case #%d:\n", casen);
    for (int i = 0; i <= r - 1; i++) {
      for (int j = 0; j <= c - 1; j++)
        printf("%c", a[i][j]);
      printf("\n");
    }
  }
  //	fclose(stdin);fclose(stdout);
  return 0;
}
