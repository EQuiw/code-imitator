#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define re(i, a, b) for (int i = a; i <= b; i++)
#define rep(i, a, b) for (int i = a; i >= b; i--)
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
  re(casen, 1, T) {
    scanf("%d%d", &r, &c);
    memset(mark, 0, sizeof(mark));
    re(i, 0, r - 1) re(j, 0, c - 1) {
      ch = getchar();
      while ((ch < 'A' || ch > 'Z') && ch != '?')
        ch = getchar();
      a[i][j] = ch;
    }
    re(i, 0, r - 1) re(j, 0, c - 1) if (a[i][j] != '?') {
      k = j + 1;
      while (k < c && a[i][k] == '?') {
        a[i][k] = a[i][j];
        k++;
      }
    }
    rep(i, r - 1, 0) rep(j, c - 1, 0) if (a[i][j] != '?') {
      k = j - 1;
      while (k >= 0 && a[i][k] == '?') {
        a[i][k] = a[i][j];
        k--;
      }
    }
    re(i, 0, r - 1) re(j, 0, c - 1) if (a[i][j] == '?') {
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

    rep(i, r - 1, 0) re(j, 0, c - 1) if (a[i][j] == '?') {
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
    re(i, 0, r - 1) {
      re(j, 0, c - 1) printf("%c", a[i][j]);
      printf("\n");
    }
  }
  //	fclose(stdin);fclose(stdout);
  return 0;
}
