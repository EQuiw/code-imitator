#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

#define DEBUG 0
#define N 1010

int main() {
  if (!DEBUG) {
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
  }
  int t, T = 1, n, m;
  char s[N];
  int f[N];
  scanf("%d", &t);
  while (t--) {
    scanf("%s%d", s, &m);
    n = strlen(s);
    for (int i = 0; i < n; ++i) {
      if (s[i] == '+') {
        f[i] = 0;
      } else {
        f[i] = 1;
      }
    }
    int ans = 0;
    for (int i = 0; i <= n - m; ++i) {
      if (f[i] == 1) {
        for (int j = 0; j < m; ++j) {
          f[i + j] ^= 1;
        }
        ++ans;
      }
    }
    for (int i = n - m + 1; i < n; ++i) {
      if (f[i] == 1) {
        ans = -1;
      }
    }
    if (ans == -1) {
      printf("Case #%d: IMPOSSIBLE\n", T++);
    } else {
      printf("Case #%d: %d\n", T++, ans);
    }
  }
  return 0;
}