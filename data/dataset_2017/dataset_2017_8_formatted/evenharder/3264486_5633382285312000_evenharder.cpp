#include <stdio.h>
#include <string.h>
#define _FILE_INPUT 0

void process() {
  int t;
  scanf("%d", &t);
  for (int t_ = 1; t_ <= t; t_++) {
    char a[30] = {};
    a[0] = '0';
    scanf("%s", a + 1);
    int l = strlen(a);
    int piv = -1;
    while (1) {
      int flag = 0;
      for (int i = 0; i < l - 1; i++) {
        if (a[i] > a[i + 1]) {
          a[i] = a[i] - 1;
          piv = i;
          for (int j = piv + 1; j < l; j++) {
            a[j] = '9';
          }
          flag = 1;
          break;
        }
      }
      if (!flag)
        break;
    }
    printf("Case #%d: ", t_);
    int zero = 1;
    for (zero = 1; zero < l; zero++) {
      if (a[zero] != '0')
        break;
    }
    puts(a + zero);
  }
}

int main() {
#if _FILE_INPUT
  freopen(".in", "r", stdin);
  freopen(".out", "w", stdout);
#endif

  process();

#if _FILE_INPUT
  fclose(stdin);
  fclose(stdout);
#endif
}