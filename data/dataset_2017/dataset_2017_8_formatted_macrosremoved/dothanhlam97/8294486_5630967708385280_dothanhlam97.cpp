#include <bits/stdc++.h>

const int N = 1000;
typedef long long ll;

using namespace std;

const double EPS = (double)(1e-9);

int main() {
  int query;
  scanf("%d", &query);
  int n;
  int D;
  int x, y;
  for (int t = 1; t <= query; t++) {
    double vmax = 0.0;
    scanf("%d %d", &D, &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d %d", &x, &y);
      int kk = D - x;
      double temp = (double)kk / (double)y;
      if (temp - vmax > -EPS) {
        vmax = temp;
      }
    }
    double v = (double)D / vmax;
    printf("Case #%d: %0.6f\n", t, v);
  }
}
