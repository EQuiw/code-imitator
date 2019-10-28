#include <bits/stdc++.h>
using namespace std;

#define maxn 2010
#define INF 0x3f3f3f3f

char s[maxn];
int dp[maxn];

int main() {
  int test, k, n, kase = 0;
  scanf("%d", &test);
  while (test--) {
    memset(dp, 0, sizeof(dp));
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    char last = '+';

    for (int i = 1; i <= n; i++) {
      if (s[i] != last) {
        dp[i] = 1;
      }
      last = s[i];
    }

    scanf("%d", &k);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      if (dp[i] == 1) {
        ans++;
        dp[i + k] ^= 1;
      }
    }

    for (int i = n + 2; i <= 2 * n; i++)
      if (dp[i] == 1)
        ans = INF;

    if (ans != INF)
      printf("Case #%d: %d\n", ++kase, ans);
    else
      printf("Case #%d: IMPOSSIBLE\n", ++kase);
  }
  return 0;
}