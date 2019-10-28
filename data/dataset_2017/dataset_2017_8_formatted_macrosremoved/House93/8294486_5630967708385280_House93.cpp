#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int T, t = 1;

int l, n;
int d[1010], f[1010];
double mt;

int main() {
  scanf("%d", &T);
  while (T--) {
    mt = 0;
    scanf("%d%d", &l, &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &d[i], &f[i]);
      double tmp = 1.0 * (l - d[i]) / f[i];
      mt = max(mt, tmp);
    }
    printf("Case #%d: %.6f\n", t++, 1.0 * l / mt);
  }
  return 0;
}
