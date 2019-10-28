#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
int T;
char a[30], ch;
int l;
int lastup, lastdown;
int now, tmp;
int main() {
  //	freopen("B.in","r",stdin);
  //	freopen("B.out","w",stdout);
  scanf("%d", &T);
  for (int casen = 1; casen <= T; casen++) {
    l = 0;
    ch = getchar();
    while (ch < '0' || ch > '9')
      ch = getchar();
    while (1) {
      while (ch < '0' || ch > '9')
        ch = getchar();
      if (l == 0 && ch == '0') {
      } else
        a[l++] = ch;
      ch = getchar();
      if (ch == '\n')
        break;
    }
    if (l == 0) {
      printf("Case #%d: 0\n", casen);

      casen++;
      continue;
    }
    if (l == 1) {
      printf("Case #%d: %c\n", casen, a[0]);
      continue;
    }
    lastup = 0;
    lastdown = 0;
    for (int i = 1; i < l; i++)
      if (a[i] > a[i - 1])
        lastup = i;
      else if (a[i] < a[i - 1]) {
        lastdown = i;
        break;
      }
    if (lastdown == 0) {
      printf("Case #%d: ", casen);
      for (int i = 0; i < l; i++)
        printf("%c", a[i]);
      printf("\n");
      continue;
    }
    a[lastup] = a[lastup] - 1;
    if (a[lastup] == '0') {
      printf("Case #%d: ", casen);
      for (int i = 1; i < l; i++)
        printf("9");
      printf("\n");
      continue;
    }
    printf("Case #%d: ", casen);
    for (int i = 0; i < lastup; i++)
      printf("%c", a[i]);
    printf("%c", a[lastup]);
    for (int i = lastup + 1; i < l; i++)
      printf("9");
    printf("\n");
  }
  ////////	fclose(stdin);
  //	fclose(stdout);
  return 0;
}
