#include <algorithm>
#include <cstdio>
using namespace std;
typedef long double LD;
#define N 1000 + 5

int Case, d, n;
LD ans;

int main() {
  scanf("%d", &Case);
  for (int T = 1; T <= Case; T++) {
    scanf("%d%d", &d, &n);
    ans = 1e14;
    for (int i = 1, k, s; i <= n; i++) {
      scanf("%d%d", &k, &s);
      LD t = (LD)(d - k) / s;
      ans = min(ans, (LD)d / t);
    }
    printf("Case #%d: %.6f\n", T, (double)ans);
  }
  return 0;
}
