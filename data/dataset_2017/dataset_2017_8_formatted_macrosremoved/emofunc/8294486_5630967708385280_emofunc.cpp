#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
int T_T;
int d, n;
int k[1111], s[1111];
int main(void) {

  scanf("%d", &T_T);
  for (int cas = 1; cas <= T_T; cas++) {
    scanf("%d%d", &d, &n);
    for (int i = 1; i <= n; i++)
      scanf("%d%d", &k[i], &s[i]);
    double mxt = 0.0;
    for (int i = 1; i <= n; i++) {
      mxt = max(mxt, (double)(d - k[i]) / (double)s[i]);
    }
    printf("Case #%d: %.6lf\n", cas, (double)d / mxt);
  }
  return 0;
}
