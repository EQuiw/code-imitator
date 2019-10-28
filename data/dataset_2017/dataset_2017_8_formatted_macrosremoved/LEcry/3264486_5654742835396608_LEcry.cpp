#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>

using namespace std;
map<long long, long long> mp;
priority_queue<long long> q;
int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("C-small-1-attempt0.out", "w", stdout);
  int tt, ri = 0;
  scanf("%d", &tt);
  while (tt--) {
    mp.clear();
    while (!q.empty())
      q.pop();
    long long n, k;
    scanf("%I64d%I64d", &n, &k);
    mp[n] = 1;
    q.push(n);
    long long ansl, ansr;
    // printf("%I64d %I64d\n",n,k);
    while (k) {
      long long now = q.top();
      q.pop();
      while (!q.empty() && q.top() == now)
        q.pop();
      long long cnt = mp[now];

      // printf("cnt:%I64d\n",cnt);
      if (cnt >= k) {
        ansl = (now - 1) / 2;
        ansr = now / 2;
        k = 0;
        break;
      }
      mp[now] = 0;
      k -= cnt;
      if (now & 1) {
        mp[now / 2] += cnt * 2;
        q.push(now / 2);
      } else {
        mp[now / 2] += cnt;
        q.push(now / 2);
        mp[(now - 1) / 2] += cnt;
        q.push((now - 1) / 2);
      }
    }
    printf("Case #%d: %I64d %I64d\n", ++ri, ansr, ansl);
  }
  return 0;
}
