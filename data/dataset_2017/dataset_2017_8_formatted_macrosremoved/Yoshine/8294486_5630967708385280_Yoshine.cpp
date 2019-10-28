#include <bits/stdc++.h>
using namespace std;

int t;
int k[1234], s[1234], n, d;

void work(int cas) {
  scanf("%d %d", &d, &n);
  double t = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &k[i], &s[i]);
    t = max(t, (double(d) - k[i]) / s[i]);
  }
  printf("Case #%d: %.7lf\n", cas, double(d) / t);
}

int main() {
  cin >> t;
  for (int _ = 1; _ <= t; _++)
    work(_);
  return 0;
}
