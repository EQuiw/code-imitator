#include <bits/stdc++.h>
#define fi(a, b, c) for (int a = b; a <= c; a++)
#define fii(a, b, c) for (int a = b; a < c; a++)
#define pb push_back
#define mp make_pair

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
  fi(t, 1, query) {
    double vmax = 0.0;
    scanf("%d %d", &D, &n);
    fi(i, 1, n) {
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