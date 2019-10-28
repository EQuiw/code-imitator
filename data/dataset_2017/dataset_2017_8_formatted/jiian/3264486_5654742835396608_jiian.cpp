#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
  freopen("123.in", "r", stdin);
  freopen("123.out", "w", stdout);
  int T, cas = 0;
  cin >> T;
  while (T--) {
    LL n, k;
    cin >> n >> k;
    int d = 0;
    for (LL v = 1; v <= k; v <<= 1)
      d++;
    printf("Case #%d: ", ++cas);
    LL base = 1 << d;
    if (n < base) {
      puts("0 0");
      continue;
    }
    LL md = (n - (base - 1)) % base;
    LL lx = (n - (base - 1)) / base, rx = lx;
    int id = k - (1 << (d - 1)) + 1;
    if (id <= md)
      rx++;
    if (id + (1 << (d - 1)) <= md)
      lx++;
    printf("%lld %lld\n", rx, lx);
  }
  return 0;
}