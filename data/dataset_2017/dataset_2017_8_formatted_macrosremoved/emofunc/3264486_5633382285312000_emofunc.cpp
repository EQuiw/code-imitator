#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
int T_T;
long long n;
bool check(long long x) {
  int last = 10;
  while (x) {
    if (x % 10 > last)
      return 0;
    last = x % 10;
    x /= 10;
  }
  return 1;
}
int main(void) {
  //    freopen("B-small-attempt0.in","r",stdin);
  //    freopen("out-small.txt","w",stdout);
  scanf("%d", &T_T);
  for (int cas = 1; cas <= T_T; cas++) {
    scanf("%lld", &n);
    long long ans;
    for (long long i = n; i >= 0; i--)
      if (check(i)) {
        ans = i;
        break;
      }
    printf("Case #%d: %lld\n", cas, ans);
  }
  return 0;
}
