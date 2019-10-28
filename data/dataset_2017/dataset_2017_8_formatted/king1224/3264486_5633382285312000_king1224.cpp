#include <cstdio>
#include <cstring>

int main() {
  int T;
  int pos;
  char input[30];
  scanf("%d%*c", &T);
  for (int l = 1; l <= T; ++l) {
    fgets(input, sizeof(input), stdin);
    pos = 0;
    int len = strlen(input);
    input[--len] = '\0';
    for (int i = 1; i < len; ++i) {
      if (input[i - 1] > input[i]) {
        --input[pos];
        for (int j = pos + 1; j < len; ++j)
          input[j] = '9';
        break;
      } else if (input[i - 1] < input[i]) {
        pos = i;
      }
    }
    pos = 0;
    while (input[pos] == '0')
      ++pos;
    printf("Case #%d: ", l);
    for (int i = pos; i < len; ++i)
      putchar(input[i]);
    puts("");
  }
  return 0;
}
