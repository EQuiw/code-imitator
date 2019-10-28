#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>

using namespace std;

const int MAXN = 1100;

int d, n;
pair<int, int> a[MAXN];

void init() {
  scanf("%d %d", &d, &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", &a[i].first, &a[i].second);
  sort(a + 1, a + n + 1);
}

void solve() {
  double ans = 0;
  for (int i = 1; i <= n; ++i) {
    double cur = (double)(d - a[i].first) / (double)a[i].second;
    if (cur > ans)
      ans = cur;
  }
  printf("%.8lf\n", (double)d / ans);
}

int main() {
  int tt;
  scanf("%d", &tt);
  for (int ii = 1; ii <= tt; ++ii) {
    init();
    printf("Case #%d: ", ii);
    solve();
  }
  return 0;
}