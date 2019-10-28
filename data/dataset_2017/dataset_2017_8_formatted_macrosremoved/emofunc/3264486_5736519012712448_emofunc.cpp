#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int T_T, K, n, A[1111][1111];
char str[1111];
int Gauss(int A[1111][1111], int n) {
  int i = 0;
  for (int j = 0; j <= n - K; j++) {
    for (int k = i + 1; k < n; k++)
      if (A[k][j]) {
        A[k][j] ^= A[i][j];
        A[k][n] ^= A[i][n];
      }
    i++;
  }
  //    printf("after elimination:\n");
  //    for (int i=0;i<n;i++)
  //    {
  //        for (int j=0;j<=n;j++) printf("%d ",A[i][j]);
  //        puts("");
  //    }
  for (i = n - K + 1; i < n; i++)
    if (A[i][n])
      break;
  if (i != n)
    return -1;
  int sum = 0;
  for (int i = 0; i <= n - K; i++)
    sum += A[i][n];
  return sum;
}
int main(void) {
  //    freopen("A-small-attempt0.in","r",stdin);
  //    freopen("out-small.txt","w",stdout);
  // freopen("a.in","r",stdin);
  scanf("%d", &T_T);
  for (int cas = 1; cas <= T_T; cas++) {
    scanf("%s%d", str, &K);
    n = strlen(str);
    memset(A, 0, sizeof(A));
    for (int i = 0; i < n; i++) {
      for (int j = max(i - K + 1, 0), sz = min(i, n - K); j <= sz; j++)
        A[i][j] = 1;
      A[i][n] = (str[i] == '-');
    }
    //        for (int i=0;i<n;i++)
    //        {
    //            for (int j=0;j<=n;j++) printf("%d ",A[i][j]);
    //            puts("");
    //        }
    int ans = Gauss(A, n);
    printf("Case #%d: ", cas);
    if (ans < 0)
      printf("IMPOSSIBLE\n");
    else
      printf("%d\n", ans);
  }
  return 0;
}
