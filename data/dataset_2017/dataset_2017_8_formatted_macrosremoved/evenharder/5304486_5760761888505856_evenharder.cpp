#include <stdio.h>
#include <string.h>

char a[30][30];
int r, c;
void process() {

  int t;
  scanf("%d", &t);
  for (int t_ = 0; t_ < t; t_++) {
    memset(a, 0, sizeof(a));
    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; i++) {
      scanf("%s", a[i]);
    }

    int done = -1;
    for (int i = 0; i < r; i++) {
      int cnt = 0;
      char prev = '?';
      for (int j = 0; j < c; j++) {
        if (a[i][j] != '?') {
          if (cnt == 0) {
            for (int k = 0; k < j; k++)
              a[i][k] = a[i][j];
          }
          prev = a[i][j];
          cnt++;
        } else {
          a[i][j] = prev;
        }
      }
      if (cnt) {
        if (done == -1) {
          for (int k = 0; k < i; k++)
            for (int j = 0; j < c; j++)
              a[k][j] = a[i][j];
        }
        done = i;
      } else if (~done) {
        for (int k = done + 1; k <= i; k++)
          for (int j = 0; j < c; j++)
            a[k][j] = a[done][j];
      }
    }
    printf("Case #%d:\n", t_ + 1);
    for (int i = 0; i < r; i++) {
      puts(a[i]);
    }
  }
}

int main() { process(); }
