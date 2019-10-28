#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1050;
double s[N], k[N], t[N];
int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  int T, ca = 1;
  scanf("%d", &T);
  while (T--) {
    printf("Case #%d: ", ca++);
    int D, n;
    scanf("%d%d", &D, &n);
    double mx = 0.0;
    for (int i = 0; i < n; i++) {
      scanf("%lf%lf", &k[i], &s[i]);
      t[i] = (D - k[i]) / s[i];
      if (mx < t[i])
        mx = t[i];
    }
    double ret = D / mx;
    printf("%.9lf\n", ret);
  }
  return 0;
}
