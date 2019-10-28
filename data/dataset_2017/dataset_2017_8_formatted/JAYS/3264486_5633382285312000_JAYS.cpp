#include <cstdio>
#include <cstring>

int N;

bool verdict(int n) {
  char m[11];
  sprintf(m, "%d", n);
  int l = strlen(m);
  for (int i = l - 1; i > 0; i--)
    if (m[i - 1] > m[i])
      return false;
  return true;
}

int solve() {
  for (int n = N; n >= 1; n--)
    if (verdict(n))
      return n;
  return 1;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d", &N);
    int ans = solve();
    printf("Case #%d: %d\n", t, ans);
  }
  return 0;
}