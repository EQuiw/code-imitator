#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

char s[2000];
int main(void) {
  int t;
  scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++) {
    int n = 0, k;
    scanf("%s%d", s, &k);
    for (int i = strlen(s) - 1; i + 1 >= k; --i) {
      if (s[i] == '-') {
        ++n;
        for (int j = 0; j < k; ++j) {
          s[i - j] = (s[i - j] == '-' ? '+' : '-');
        }
      }
      // printf("%c %s\n", s[i], s);
    }
    for (int j = 0; j < k; ++j) {
      if (s[j] == '-') {
        n = -1;
      }
    }

    if (n < 0) {
      printf("Case #%d: IMPOSSIBLE\n", tt);
      continue;
    }
    printf("Case #%d: %d\n", tt, n);
  }
  return 0;
}
