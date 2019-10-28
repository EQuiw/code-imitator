#include <bits/stdc++.h>

using namespace std;

int t, n, k;
char inp[1005];

#define SMALL

int main()
{
#ifdef SMALL
  freopen("A-small.in", "r", stdin);
  freopen("A-small.out", "w", stdout);
#endif
  scanf("%d", &t);
  for (int Case = 1; Case <= t; ++Case) {
    scanf("%s %d", inp, &k);
    n = strlen(inp);
    int ans = 0;
    for (int i = 0; i < n; ++i)
      if (inp[i] == '-' && i + k <= n && ++ans)
        for (int j = 0; j < k; ++j)
          inp[i + j] = inp[i + j] == '+' ? '-' : '+';
    for (int i = 0; i < n; ++i)
      if (inp[i] == '-')
        ans = -1;
    printf("Case #%d: ", Case);
    if (ans == -1)
      printf("IMPOSSIBLE\n");
    else
      printf("%d\n", ans);
  }
  return 0;
}