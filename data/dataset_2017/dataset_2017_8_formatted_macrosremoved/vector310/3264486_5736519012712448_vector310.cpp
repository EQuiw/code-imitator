#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
char s[1010];
int m, n;
int main() {
  // freopen("in.txt","r",stdin);
  // freopen("out.txt","w",stdout);
  int T;
  cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s + 1);
    scanf("%d", &m);
    n = strlen(s + 1);
    int ans = 0;
    for (int i = 1; i <= n - m + 1; ++i) {
      if (s[i] == '-') {
        ++ans;
        for (int j = 1; j <= m; ++j)
          if (s[i + j - 1] == '+')
            s[i + j - 1] = '-';
          else
            s[i + j - 1] = '+';
      }
    }
    bool flag = 1;
    for (int i = 1; i <= n; ++i)
      if (s[i] == '-')
        flag = 0;
    if (flag)
      printf("Case #%d: %d\n", cas, ans);
    else
      printf("Case #%d: IMPOSSIBLE\n", cas);
  }
}
