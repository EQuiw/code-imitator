#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll dp(ll num, ll ma) {
  if (num < 10) {
    return min(num, ma);
  }
  ll ret = 0;
  ll ldig = min(ma, num%10);
  ll rem = num/10;
  ll tmp = dp(rem, ldig);
  if (tmp > 0) ret = tmp*10+ldig;
  ldig = 9;
  rem -= 1;
  return max(ret, dp(rem, ldig)*10+ldig);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    ll s;
    scanf("%lld", &s);
    printf("Case #%d: %lld\n", cas, dp(s, 9));
  }
}
