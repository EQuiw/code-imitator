#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int R[50], Q[50][50];
int dp[1 << 8][1 << 8] = {};

int solve() {
  memset(dp, 0, sizeof(dp));

  int N, P;
  cin >> N >> P;

  for (int(i) = 0; (i) < (int)(N); ++(i))
    cin >> R[i];
  for (int(i) = 0; (i) < (int)(N); ++(i))
    for (int(j) = 0; (j) < (int)(P); ++(j))
      cin >> Q[i][j];

  int ret = 0;
  if (N == 1) {
    for (int(i) = 0; (i) < (int)(P); ++(i)) {
      int p = Q[0][i] / R[0];
      for (ll k = 1; k <= 1000000; ++k) {
        ll x = k * R[0];
        if (9 * x <= 10 * Q[0][i] && 10 * Q[0][i] <= 11 * x) {
          ++ret;
          break;
        }
      }
    }
  }
  if (N == 2) {
    int ok[8][8] = {};
    for (int(i) = 0; (i) < (int)(P); ++(i))
      for (int(j) = 0; (j) < (int)(P); ++(j)) {
        int p = Q[0][i] / R[0];
        // printf(" p =%d\n", p);
        for (ll k = 1; k <= 1000000; ++k) {
          ll x = k * R[0];
          ll y = k * R[1];

          if (9 * x <= 10 * Q[0][i] && 10 * Q[0][i] <= 11 * x &&
              9 * y <= 10 * Q[1][j] && 10 * Q[1][j] <= 11 * y) {
            // printf("ok (%d,%d)\n", i,j);
            // printf("x, y %d %d\n", x,y);
            ok[i][j] = 1;
            break;
          }
        }
      }

    for (int(m1) = 0; (m1) < (int)(1 << P); ++(m1))
      for (int(m2) = 0; (m2) < (int)(1 << P); ++(m2)) {
        // 次にiとjのペアを採用
        for (int(i) = 0; (i) < (int)(P); ++(i))
          for (int(j) = 0; (j) < (int)(P); ++(j)) {
            if (m1 >> i & 1)
              continue;
            if (m2 >> j & 1)
              continue;

            if (ok[i][j])
              dp[m1 + (1 << i)][m2 + (1 << j)] =
                  max(dp[m1 + (1 << i)][m2 + (1 << j)], dp[m1][m2] + 1);
          }
      }

    for (int(m1) = 0; (m1) < (int)(1 << P); ++(m1))
      for (int(m2) = 0; (m2) < (int)(1 << P); ++(m2))
        ret = max(ret, dp[m1][m2]);
  }

  return ret;
}

int main() {
  int T;
  cin >> T;
  for (int(t) = 0; (t) < (int)(T); ++(t)) {
    printf("Case #%d: %d\n", t + 1, solve());
  }
  return 0;
}
