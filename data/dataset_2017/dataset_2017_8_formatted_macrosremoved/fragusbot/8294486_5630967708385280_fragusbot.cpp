#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

int a[N];
long long b[N];

int main() {
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
  int tt;
  scanf("%d", &tt);
  for (int cc = 1; cc <= tt; ++cc) {
    double begt = clock();
    printf("Case #%d: ", cc);
    int d, n;
    scanf("%d %d", &d, &n);
    for (int i = 0; i < n; ++i) {
      int foo, bar;
      scanf("%d %d", &foo, &bar);
      a[i] = d - foo;
      b[i] = 1LL * d * bar;
    }
    long double l = 0, r = 1e16;
    for (int it = 0; it < 1000; ++it) {
      long double s = (l + r) * 0.5;
      bool can = true;
      for (int i = 0; i < n; ++i) {
        if (b[i] < a[i] * s) {
          can = false;
        }
      }
      if (can) {
        l = s;
      } else {
        r = s;
      }
    }
    printf("%.15f\n", (double)((l + r) * 0.5));
    fprintf(stderr, "case %d solved in %.3f\n", cc,
            (clock() - begt) / CLOCKS_PER_SEC);
  }
}
