#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int cnt[5], b[5];

int main() {
  freopen("A-small-attempt1.in", "r", stdin);
  freopen("123.out", "w", stdout);
  int T, cas = 0;
  scanf("%d", &T);
  while (T--) {
    int n, p;
    scanf("%d %d", &n, &p);
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < n; i++) {
      int x;
      scanf("%d", &x);
      cnt[x % p]++;
    }
    int ans;
    if (p == 2) {
      ans = n - cnt[1] / 2;
    } else if (p == 3) {
      int x = min(cnt[1], cnt[2]);
      cnt[1] -= x;
      cnt[2] -= x;
      ans = cnt[0];
      ans += x;
      ans += cnt[1] / 3 + cnt[2] / 3;
      if (cnt[1] % 3)
        ans++;
      if (cnt[2] % 3)
        ans++;
    } else if (p == 4) {
      int x = min(cnt[1], cnt[3]);
      ans = cnt[0] + cnt[2] / 2 + x;
      cnt[1] -= x;
      cnt[3] -= x;
      if (cnt[2] & 1) {
        if (cnt[1] > 1) {
          ans++;
          cnt[1] -= 2;
        } else if (cnt[3] > 1) {
          ans++;
          cnt[3] -= 2;
        }
      }
      ans += cnt[1] / 4 + cnt[3] / 4;
      if (cnt[1] % 4)
        ans++;
      if (cnt[3] % 4)
        ans++;
    }

    printf("Case #%d: %d\n", ++cas, ans);
  }
  return 0;
}
