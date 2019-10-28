#include <cstdio>
using namespace std;
long long f[30], ans, n, m;
int a[30], l;
void work() {
  int j, i, k;
  for (j = l; j >= 1; j--) {
    if (a[j] < a[j + 1])
      return;
    if (a[j] == a[j + 1])
      continue;
    ans = 0;
    for (k = l; k >= j + 1; k--) {
      ans += a[k] * f[k];
    }
    ans += (a[j] - 1) * f[j];
    for (i = 1; i < j; i++)
      ans += 9 * f[i];
  }
  ans = m;
  return;
}
int main() {
  int i, j, k, test;
  freopen("b.out", "w", stdout);
  f[1] = 1;
  for (i = 2; i <= 19; i++)
    f[i] = f[i - 1] * 10;
  scanf("%d", &test);
  for (int kase = 1; kase <= test; kase++) {
    scanf("%lld", &n);
    l = 0;
    m = n;
    while (n != 0) {
      l++;
      a[l] = n % 10;
      n /= 10;
    }
    a[l + 1] = 0;
    work();
    printf("Case #%d: %lld\n", kase, ans);
  }
  fclose(stdout);
}
