#include <algorithm>
#include <cstdio>
#include <cstring>

int T, N;
char in[19];
char make[19];

bool check() {
  char curr = '1';
  for (int i = 0; i < N; i++) {
    if (make[i] < curr) {
      return false;
    }
    curr = make[i];
  }
  return true;
}

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);
  scanf("%d", &T);
  for (int tc = 1; tc <= T; tc++) {
    scanf("%s", in);
    N = strlen(in);
    bool found = false;
    for (int k = N; k >= 0; k--) {
      // case 1: 0~k same k+1~N-1 to fit
      for (int i = 0; i < k; i++) {
        make[i] = in[i];
      }
      make[k] = in[k] - 1;
      for (int i = k + 1; i < N; i++) {
        make[i] = '9';
      }
      make[N] = '\0';
      found = check();
      if (found)
        break;
    }
    if (!found) {
      // case 2: fill with 999999...
      for (int i = 0; i < N - 1; i++) {
        make[i] = '9';
      }
      make[N - 1] = '\0';
    }
    printf("Case #%d: %s\n", tc, make);
  }
  return 0;
}
