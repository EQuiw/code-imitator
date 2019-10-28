#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>

using namespace std;

int k[2000], s[2000], d, n;

int main() {
  // freopen("a.in","r",stdin);
  // freopen("a.out","w",stdout);
  int T, w = 0;
  for (scanf("%d", &T); T--;) {
    scanf("%d%d", &d, &n);
    for (int i = 1; i <= n; i++)
      scanf("%d%d", &k[i], &s[i]);
    double temp = 0;
    for (int i = 1; i <= n; i++)
      temp = max(temp, (double)(d - k[i]) / (double)s[i]);
    printf("Case #%d: %.6lf\n", ++w, (double)d / temp);
  }
  return 0;
}
