#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 1010

int T, t = 1;

int l, n;
int d[N], f[N];
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
