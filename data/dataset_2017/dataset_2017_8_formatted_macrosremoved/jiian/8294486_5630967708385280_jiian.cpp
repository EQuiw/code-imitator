#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
  freopen("123.in", "r", stdin);
  freopen("123.out", "w", stdout);
  int T, cas = 0;
  cin >> T;
  while (T--) {
    int d, n;
    cin >> d >> n;
    double t = 0;
    while (n--) {
      int k, s;
      cin >> k >> s;
      t = max((1.0 * d - k) / s, t);
    }
    double ans = d / t;
    printf("Case #%d: %.10f\n", ++cas, ans);
  }
  return 0;
}
