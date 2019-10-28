#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

long long pot[20];
vector<long long> cs;

long long test(long long val) {
  long long v = val;
  int last = 9;
  while (v > 0) {
    // printf("%lld\n",v);
    int at = v % 10;
    v /= 10;
    if (last < at)
      return 0;
    else
      last = at;
  }
  return val;
}

int main() {
  int t;
  scanf("%d", &t);
  pot[0] = 1;
  for (int i = 1; i <= 18; i++) {
    pot[i] = pot[i - 1] * 10LL;
    // printf("%lld\n",pot[i]);
  }
  for (int cas = 0; cas < t; cas++) {
    cs.clear();
    long long a;
    scanf("%lld", &a);
    // printf("%lld\n",a);
    cs.push_back(a);
    for (int i = 1; i <= 18; i++) {
      long long aux = a % pot[i];
      // printf("alive\n");
      aux = a - aux - 1;
      if (aux > 0) {
        cs.push_back(aux);
      }
    }
    long long ans = 0;
    for (int i = 0; i < cs.size(); i++) {
      ans = max(ans, test(cs[i]));
    }
    printf("Case #%d: %lld\n", cas + 1, ans);
  }
}
