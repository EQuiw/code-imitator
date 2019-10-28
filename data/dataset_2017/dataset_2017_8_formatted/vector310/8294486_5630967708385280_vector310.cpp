#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define rep(i, l, r) for (int i = l; i <= r; ++i)
using namespace std;
const int maxn = 1010;
int k[maxn], s[maxn];
double runtime[maxn];
int main() {
  // freopen("in.txt","r",stdin);
  // freopen("out.txt","w",stdout);
  int T;
  cin >> T;
  rep(cas, 1, T) {
    int d, n;
    double v = -1.0;
    cin >> d >> n;
    rep(i, 1, n) scanf("%d%d", &k[i], &s[i]);
    rep(i, 1, n) {
      runtime[i] = (double)(d - k[i]) / s[i];
      rep(j, 1, n) if (s[i] > s[j] && k[i] <= k[j]) {
        int delta = k[j] - k[i];
        double t = (double)delta / (s[i] - s[j]);
        if (t < runtime[i])
          runtime[i] = t;
      }
    }
    rep(i, 1, n) if (v < 0 || v > (k[i] + runtime[i] * s[i]) / runtime[i]) {
      v = (k[i] + runtime[i] * s[i]) / runtime[i];
    }
    printf("Case #%d: %.8f\n", cas, v);
  }
  return 0;
}
