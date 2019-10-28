#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  int T;
  cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    ll T, K;
    cin >> T >> K;
    ll num1 = T, num2 = 0;
    ll cnt1 = 1, cnt2 = 0;
    ll ans = 0;
    for (ll top = 2;; top <<= 1) {
      if (top > K) {
        ll rank = K - top / 2 + 1;
        ans = rank <= cnt1 ? num1 : num2;
        break;
      }
      if (num1 & 1) {
        cnt1 = cnt1 * 2 + cnt2;
        cnt2 = cnt2;
      } else {
        cnt1 = cnt1;
        cnt2 = cnt2 * 2 + cnt1;
      }
      num1 = num1 / 2;
      num2 = num1 - 1;
    }
    printf("Case #%d: %lld %lld\n", cas, ans / 2, ans - 1 - ans / 2);
  }
}
