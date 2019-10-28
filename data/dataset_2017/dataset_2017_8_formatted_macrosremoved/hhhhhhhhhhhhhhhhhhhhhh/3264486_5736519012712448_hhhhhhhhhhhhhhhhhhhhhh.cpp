#include <bits/stdc++.h>
using namespace std;

char s[1010];

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);

  int test;
  scanf("%d", &test);
  for (int _ = 1; _ <= test; _++) {
    scanf("%s", s);
    int K;
    scanf("%d", &K);

    int lens = strlen(s), ret = 0;

    for (int i = 0; i + K <= lens; i++) {
      if (s[i] == '-') {
        for (int j = i; j < i + K; j++) {
          if (s[j] == '-')
            s[j] = '+';
          else
            s[j] = '-';
        }
        ret++;
      }
    }
    bool judge = true;
    for (int i = 0; i < lens; i++) {
      if (s[i] == '-') {
        judge = false;
      }
    }

    printf("Case #%d: ", _);
    if (judge)
      printf("%d\n", ret);
    else
      puts("IMPOSSIBLE");
  }

  return 0;
}
