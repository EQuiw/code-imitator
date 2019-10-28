#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int hk, ak, hd, ad, b, d, ans;

void Work(int x, int y) {
  int p = 0, hh = hd, aa = ad, h = hk, a = ak;
  while (h > 0) {
    if (hd - a <= 0)
      return;
    if (h - aa <= 0) {
      p++;
      break;
    }
    if (hh - a <= 0 && hd - a - a <= 0)
      return;
    if (hh - a <= 0)
      hh = hd;
    else if (x > 0)
      a = max(a - d, 0), x--;
    else if (y > 0)
      aa += b, y--;
    else
      h -= aa;
    p++;
    hh -= a;
    if (p > ans)
      break;
    // printf("%d %d %d %d\n",hh,h,a,p);
  }
  ans = min(ans, p);
  // printf("%d\n",ans);
}

int main() {
  // freopen("c.in","r",stdin);
  // freopen("c.out","w",stdout);
  int T, w = 0;
  for (scanf("%d", &T); T--;) {
    scanf("%d%d%d%d%d%d", &hd, &ad, &hk, &ak, &b, &d);
    ans = 1e9 + 10;
    for (int i = 0; i <= 101; i++)
      for (int j = 0; j <= 101; j++)
        Work(i, j);
    Work(0, 0);
    printf("Case #%d: ", ++w);
    if (ans == 1e9 + 10)
      printf("IMPOSSIBLE\n");
    else
      printf("%d\n", ans);
  }
  return 0;
}
