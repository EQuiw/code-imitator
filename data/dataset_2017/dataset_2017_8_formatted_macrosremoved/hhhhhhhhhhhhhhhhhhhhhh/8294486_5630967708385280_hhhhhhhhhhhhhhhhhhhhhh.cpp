#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int test;
  scanf("%d", &test);
  for (int _ = 1; _ <= test; _++) {
    int d, n;
    scanf("%d%d", &d, &n);

    double mx = 0;
    for (int i = 0; i < n; i++) {
      int x, v;
      scanf("%d%d", &x, &v);
      mx = max(mx, (d - x) * 1.0 / v);
    }

    printf("Case #%d: %.10f\n", _, d / mx);
  }
  return 0;
}
