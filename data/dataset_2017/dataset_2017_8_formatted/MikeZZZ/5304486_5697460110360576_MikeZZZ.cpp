#include <bits/stdc++.h>
using namespace std;
const int N = 50 + 5;
int T, Case, n, p;
int a[N], b[N][N];

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("out0.out", "w", stdout);
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &p);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        scanf("%d", &b[i][j]);
        b[i][j] *= 10;
      }
    }
    if (n == 1) {
      int ans = 0;
      for (int i = 0; i < p; i++) {
        int cnt = b[0][i] / (9 * a[0]);
        while (1) {
          long long cur = b[0][i];
          if (cur < 9LL * cnt * a[0])
            break;
          if (cur >= 9LL * cnt * a[0] && cur <= 11LL * cnt * a[0]) {
            ans++;
            break;
          }
          cnt++;
        }
      }
      printf("Case #%d: %d\n", ++Case, ans);
    } else {
      sort(b[0], b[0] + p);
      sort(b[1], b[1] + p);
      int ans = 0;
      do {
        int ansCur = 0;
        for (int i = 0; i < p; i++) {
          int cnt = min(b[0][i] / (9 * a[0]), b[1][i] / (9 * a[1]));
          while (1) {
            long long cur1 = b[0][i], cur2 = b[1][i];
            if (cur1 < 9LL * cnt * a[0] || cur2 < 9LL * cnt * a[1])
              break;
            if (cur1 >= 9LL * cnt * a[0] && cur1 <= 11LL * cnt * a[0] &&
                cur2 >= 9LL * cnt * a[1] && cur2 <= 11LL * cnt * a[1]) {
              ansCur++;
              break;
            }
            cnt++;
          }
        }
        ans = max(ans, ansCur);
      } while (next_permutation(b[1], b[1] + p));
      printf("Case #%d: %d\n", ++Case, ans);
    }
  }
  return 0;
}
