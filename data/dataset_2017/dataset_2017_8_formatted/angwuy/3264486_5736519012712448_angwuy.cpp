#include <cstdio>
#include <cstring>

const int MAXN = 1100;

int n, s;
char a[MAXN];

void solve() {
  scanf("%s %d", a + 1, &s);
  n = strlen(a + 1);
  int ans = 0;
  for (int i = 1; i <= n - s + 1; ++i)
    if (a[i] == '-') {
      ++ans;
      for (int j = i; j <= i + s - 1; ++j)
        a[j] ^= ('-' ^ '+');
    }
  for (int i = 1; i <= n; ++i)
    if (a[i] == '-') {
      printf("IMPOSSIBLE\n");
      return;
    }
  printf("%d\n", ans);
}

int main() {
  int tt;
  scanf("%d", &tt);
  for (int ii = 1; ii <= tt; ++ii) {
    printf("Case #%d: ", ii);
    solve();
  }
  return 0;
}