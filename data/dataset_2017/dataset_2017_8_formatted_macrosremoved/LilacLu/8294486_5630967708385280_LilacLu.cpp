#include <bits/stdc++.h>

using namespace std;

//#define LARGE

int d, n;
int init[1005], s[1005];

int main() {

  freopen("A-small.in", "r", stdin);
  freopen("A-small.out", "w", stdout);

  int T;
  scanf("%d", &T);
  for (int Case = 1; Case <= T; ++Case) {
    scanf("%d %d", &d, &n);
    for (int i = 0; i < n; ++i)
      scanf("%d %d", &init[i], &s[i]);
    double minT = 0;
    for (int i = n - 1; i > -1; --i) {
      double temp = (1.0 * d - init[i]) / s[i];
      minT = max(temp, minT);
    }
    printf("Case #%d: %.9lf\n", Case, d / minT);
  }
  return 0;
}
