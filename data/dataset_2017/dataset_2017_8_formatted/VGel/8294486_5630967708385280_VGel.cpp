#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
const int N = 1200;
int T_T;
int d, n;
int k[N], s[N];
template <typename T> inline void read(T &x) {
  x = 0;
  bool f = false;
  char ch = getchar();
  while (ch < '0' || '9' < ch) {
    if (ch == '-')
      f = !f;
    ch = getchar();
  }
  while ('0' <= ch && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  if (f)
    x = -x;
}
int main() {
#ifdef VGel
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif VGel
  read(T_T);
  for (int T = 1; T <= T_T; T++) {
    read(d);
    read(n);
    for (int i = 1; i <= n; i++)
      read(k[i]), read(s[i]);
    double ans = 0.0;
    for (int i = 1; i <= n; i++)
      ans = max(ans, 1.0 * (d - k[i]) / s[i]);
    printf("Case #%d: %.6lf\n", T, (double)d / ans);
  }
  return 0;
}
