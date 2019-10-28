#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int maxn = 1010;
int k[maxn], s[maxn];
double runtime[maxn];
int main() {
  // freopen("in.txt","r",stdin);
  // freopen("out.txt","w",stdout);
  int T;
  cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    int d, n;
    double v = -1.0;
    cin >> d >> n;
    for (int i = 1; i <= n; ++i)
      scanf("%d%d", &k[i], &s[i]);
    for (int i = 1; i <= n; ++i) {
      runtime[i] = (double)(d - k[i]) / s[i];
      for (int j = 1; j <= n; ++j)
        if (s[i] > s[j] && k[i] <= k[j]) {
          int delta = k[j] - k[i];
          double t = (double)delta / (s[i] - s[j]);
          if (t < runtime[i])
            runtime[i] = t;
        }
    }
    for (int i = 1; i <= n; ++i)
      if (v < 0 || v > (k[i] + runtime[i] * s[i]) / runtime[i]) {
        v = (k[i] + runtime[i] * s[i]) / runtime[i];
      }
    printf("Case #%d: %.8f\n", cas, v);
  }
  return 0;
}
