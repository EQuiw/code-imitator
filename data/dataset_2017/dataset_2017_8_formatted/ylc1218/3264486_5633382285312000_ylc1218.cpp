#include <cstdio>
#include <cstdlib>
#include <cstring>

int T, L;
char str[20];

int main() {
  scanf("%d", &T);

  for (int t = 1; t <= T; t++) {
    scanf("%s", str);
    L = strlen(str);

    for (int i = 1; i < L; i++) {
      if (str[i] < str[i - 1]) {
        for (int j = i; j < L; j++) {
          str[j] = '9';
        }
        str[i - 1]--;

        i--;
        while (i > 0 && str[i] < str[i - 1]) {
          str[i] = '9';
          str[i - 1]--;
          i--;
        }
        break;
      }
    }

    long long ans = 0;
    for (int i = 0; i < L; i++) {
      ans = ans * 10 + str[i] - '0';
    }

    printf("Case #%d: %lld\n", t, ans);
  }
  return 0;
}
