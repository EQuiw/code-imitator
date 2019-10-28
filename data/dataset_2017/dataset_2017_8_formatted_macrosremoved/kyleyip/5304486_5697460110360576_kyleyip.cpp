#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
int test, n, p, i, j, l, r, a[100][100], b[100][100], c[100], num[100],
    f[10010];
bool cmp(int i, int j) {
  if (b[1][i] < a[2][j])
    return 0;
  if (b[2][j] < a[1][i])
    return 0;
  // if (a[1][i]<=a[2][j]&&a[2][j]<=b[1][i]) return 1;
  // if (a[1][i]<=b[2][j]&&b[2][j]<=b[1][i]) return 1;
  // if (a[2][j]<=a[1][i]&&b[1][i]<=b[2][j]) return 1;
  return 1;
}
int main() {
  // freopen("b.in","r",stdin);
  // freopen("b2.out","w",stdout);
  scanf("%d", &test);
  for (int kase = 1; kase <= test; kase++) {
    scanf("%d%d", &n, &p);
    for (i = 1; i <= n; i++)
      scanf("%d", &c[i]);
    for (i = 1; i <= n; i++) {
      num[i] = 0;
      for (j = 1; j <= p; j++) {
        int x;
        scanf("%d", &x);
        l = (ceil)((double)x / 1.1 / (double)c[i]);
        r = (floor)((double)x / 0.9 / (double)c[i]);
        if (l <= 0)
          l = 1;
        if (l <= r) {
          ++num[i];
          a[i][num[i]] = l;
          b[i][num[i]] = r;
        }
      }
    }
    printf("Case #%d: ", kase);
    int ans = num[1];
    for (i = 1; i <= n; i++)
      if (num[i] < ans)
        ans = num[i];
    if (ans == 0) {
      printf("0\n");
      continue;
    }
    if (n == 1) {
      printf("%d\n", num[1]);
      continue;
    }
    if (n == 2) {
      ans = 0;
      int m = 1 << num[2];
      memset(f, 0, sizeof(f));
      for (i = 1; i <= num[1]; i++)
        for (j = 0; j < m; j++) {
          for (int k = 1; k <= num[2]; k++)
            if (!(j & (1 << (k - 1)))) {
              // printf("111111111\n");
              if (cmp(i, k)) {
                // if (k==2) {printf("111111111 ");printf("%d\n",j);}
                // printf("11111111\n");
                int now = j | (1 << (k - 1));
                if (f[now] < f[j] + 1) {
                  f[now] = f[j] + 1;
                } // printf("%d\n",now);}
                if (ans < f[now])
                  ans = f[now];
              }
            }
        }
      printf("%d\n", ans);
    }
  }
  // fclose(stdin);fclose(stdout);
}
