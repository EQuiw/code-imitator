#include <stdio.h>
#include <string.h>

char s[1001];
int K, len, i, j, cnt;

int main() {
  int cases;
  scanf("%d", &cases);
  for (int kejs = 1; kejs <= cases; kejs++) {
    printf("Case #%d: ", kejs);
    scanf("%s%d", s, &K);
    len = strlen(s);
    cnt = 0;
    for (i = 0; i <= len - K; i++) {
      if (s[i] == '+')
        continue;
      cnt++;
      for (j = 0; j < K; j++) {
        if (s[i + j] == '-')
          s[i + j] = '+';
        else
          s[i + j] = '-';
      }
    }
    for (; i < len; i++) {
      if (s[i] == '-')
        cnt = -1;
    }
    if (cnt == -1)
      printf("IMPOSSIBLE\n");
    else
      printf("%d\n", cnt);
  }
  return 0;
}
