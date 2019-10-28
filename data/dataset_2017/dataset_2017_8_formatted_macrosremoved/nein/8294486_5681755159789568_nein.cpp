#include <bits/stdc++.h>

int e[110];
int s[110];
int matrix[110][110];
double dy[110];
bool chk[110];
int main() {
  int tc;
  scanf("%d", &tc);
  int P = 0;
  while (tc--) {

    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
      chk[i] = 0;
      dy[i] = 0;
      scanf("%d%d", &e[i], &s[i]);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%d", &matrix[i][j]);
      }
    }
    double ans = 0;
    while (q--) {
      int u, v;
      scanf("%d%d", &u, &v);
      for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i + 1; j < n; j++) {
          sum += matrix[j - 1][j];
          if (sum <= e[i]) {
            if (!chk[j]) {
              dy[j] = dy[i] + ((double)sum) / s[i];
              chk[j] = true;
            } else
              dy[j] = std::min(dy[j], dy[i] + ((double)sum) / s[i]);
          } else {
            break;
          }
        }
      }
      ans = dy[n - 1];
    }

    P++;
    printf("Case #%d: %.10lf\n", P, ans);
  }
}
