#include <algorithm>
#include <functional>
#include <map>
#include <stdio.h>
#define _FILE_INPUT 0
typedef long long int ll;

void process() {
  int t;
  scanf("%d", &t);
  for (int t_ = 1; t_ <= t; t_++) {
    ll n, k, x;
    scanf("%lld%lld", &n, &k);
    std::map<ll, ll, std::greater<ll>> m;
    m[n] = 1LL;
    x = 0LL;
    while (1) {
      ll num = m.begin()->first;  // m['n']
      ll siz = m.begin()->second; // 'm[n]'
      ll l = num / 2;
      ll r = (num - 1) / 2;
      if (x + siz >= k) {
        printf("Case #%d: ", t_);
        printf("%lld %lld\n", l, r);
        break;
      } else {
        m.erase(m.begin());
        m[l] = m[l] + siz;
        m[r] = m[r] + siz;
        x = x + siz;
      }
    }
  }
}

int main() {
#if _FILE_INPUT
  freopen(".in", "r", stdin);
  freopen(".out", "w", stdout);
#endif

  process();

#if _FILE_INPUT
  fclose(stdin);
  fclose(stdout);
#endif
}