#include <cstdio>
#include <cstring>
using namespace std;
bool a[1010];
int b[1010];
int t, n, k, j, l, c, m, i, max1, max2, maxi, now1, now2;
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int main() {
  // freopen("c.out","w",stdout);
  scanf("%d", &t);
  for (int kase = 1; kase <= t; kase++) {
    scanf("%d%d", &n, &k);
    memset(a, 0, sizeof(a));
    a[0] = 1;
    a[n + 1] = 1;
    for (i = 1; i <= k; i++) {
      l = 1;
      b[1] = 0;
      for (j = 1; j <= n + 1; j++)
        if (a[j] == 1)
          b[++l] = j;
      max1 = -1;
      max2 = -1;
      maxi = 0;
      for (j = 1; j < l; j++) {
        if (b[j + 1] - b[j] == 1)
          continue;
        c = (b[j + 1] + b[j] + 1) / 2 - 1;
        for (m = 1; m <= 3; m++) {
          now1 = min(c - b[j], b[j + 1] - c) - 1;
          if (now1 < max1)
            continue;
          now2 = max(c - b[j], b[j + 1] - c) - 1;
          if (now1 > max1) {
            max1 = now1;
            max2 = now2;
            maxi = c;
          } else {
            if (now2 < max2)
              continue;
            if (now2 > max2) {
              max2 = now2;
              maxi = c;
            } else if (c < maxi) {
              maxi = c;
            }
          }
          c++;
        }
      }
      a[maxi] = 1;
    }
    printf("Case #%d: %d %d\n", kase, max2, max1);
  }
  // fclose(stdout);
}
