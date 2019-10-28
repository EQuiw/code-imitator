#include <stdio.h>
#include <string.h>

int a[1003];

void process() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    char a[1003] = {};
    int k;
    int ans = 0;
    int flag = 0;
    scanf("%s%d", a, &k);
    int l = strlen(a);
    for (int j = 0; j <= l - k; j++) {
      if (a[j] == '-') {
        for (int x = j; x < j + k; x++) {
          if (a[x] == '-')
            a[x] = '+';
          else
            a[x] = '-';
        }
        ans++;
      }
    }
    for (int j = l - k; j < l; j++) {
      if (a[j] == '-') {
        flag = 1;
        break;
      }
    }
    printf("Case #%d: ", i + 1);
    if (flag)
      printf("IMPOSSIBLE\n");
    else
      printf("%d\n", ans);
  }
}

int main() { process(); }
