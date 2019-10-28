#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 5;
const double EPS = 1e-3;
int R[55];
int q[55][55];
int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B.out", "w", stdout);
  int t, ca = 1;
  scanf("%d", &t);
  while (t--) {
    printf("Case #%d: ", ca++);
    int n, p;
    scanf("%d%d", &n, &p);
    for (int i = 0; i < n; i++)
      scanf("%d", &R[i]);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < p; j++)
        scanf("%d", &q[i][j]);
    int ans = 0;
    for (int i = 0; i < p; i++) {
      int l = INT_MAX, r = 0;
      for (int j = 0; j < n; j++) {
        int a = ceil(q[j][i] / (R[j] * 0.9));
        int b = ceil(q[j][i] / (R[j] * 1.1));
        if ((int)(a * R[j] * 0.9) > q[j][i])
          a--;
        if ((int)(b * R[j] * 1.1) < q[j][i])
          b--;
        if (a < b || a <= 0 || b <= 0) {
          l = INT_MAX, r = 0;
          break;
        }
        if (l != INT_MAX && (r < b || l > a)) {
          l = INT_MAX, r = 0;
          break;
        }
        l = min(l, a), l = min(l, b);
        r = max(r, a), r = max(r, b);
      }
      if (l != INT_MAX && r >= l)
        ans++;
    }

    int ans2 = 0;
    for (int i = 0; i < n; i++)
      sort(q[i], q[i] + p);
    for (int i = 0; i < p; i++) {
      int l = INT_MAX, r = 0;
      for (int j = 0; j < n; j++) {
        int a = ceil(q[j][i] / (R[j] * 0.9));
        int b = ceil(q[j][i] / (R[j] * 1.1));
        if ((int)(a * R[j] * 0.9) > q[j][i])
          a--;
        if ((int)(b * R[j] * 1.1) < q[j][i])
          b--;
        if (a < b || a <= 0 || b <= 0) {
          l = INT_MAX, r = 0;
          break;
        }
        if (l != INT_MAX && (r < b || l > a)) {
          l = INT_MAX, r = 0;
          break;
        }
        l = min(l, a), l = min(l, b);
        r = max(r, a), r = max(r, b);
      }
      if (l != INT_MAX && r >= l)
        ans2++;
    }
    printf("%d\n", max(ans, ans2));
  }
  return 0;
}
