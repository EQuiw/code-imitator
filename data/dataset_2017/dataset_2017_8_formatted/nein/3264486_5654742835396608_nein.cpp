#include <bits/stdc++.h>

std::map<long long, long long, std::greater<long long>> map;
long long minV(long long a) { return (a - 1) / 2; }
long long maxV(long long a) { return a / 2; }
int main() {
  int tc;
  scanf("%d", &tc);
  int q = 0;
  while (tc--) {
    long long n;
    long long k;
    scanf("%lld%lld", &n, &k);
    map.clear();
    map[n]++;
    q++;
    printf("Case #%d: ", q);
    while (true) {
      long long p = (*map.begin()).first;
      long long cnt = (*map.begin()).second;
      map.erase(map.begin());
      map[maxV(p)] += cnt;
      map[minV(p)] += cnt;
      if (cnt >= k) {
        printf("%lld %lld\n", maxV(p), minV(p));
        break;
      } else {
        k -= cnt;
      }
    }
  }
}