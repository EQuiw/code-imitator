#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long LL;

int Case;
LL n, k;

LL dfs(LL u_1, LL c_1, LL u_2, LL c_2, LL t) {
  if (t <= c_1)
    return u_1;
  if (t <= c_1 + c_2)
    return u_2;
  LL v_1 = u_1 >> 1, v_2 = v_1 - 1;
  LL d_1 = c_1 + (u_1 & 1 ? c_1 + c_2 : 0), d_2 = (c_1 + c_2 << 1) - d_1;
  return dfs(v_1, d_1, v_2, d_2, t - c_1 - c_2);
}

int main() {
  scanf("%d", &Case);
  for (int T = 1; T <= Case; T++) {
    printf("Case #%d: ", T);
    scanf("%lld%lld", &n, &k);
    LL res = dfs(n + 1, 0, n, 1, k);
    printf("%lld %lld\n", res >> 1, res - 1 >> 1);
  }
  return 0;
}
