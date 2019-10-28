#include <cstdio>
#include <cstring>
#include <iostream>
#define rep(i, l, r) for (int i = l; i <= r; ++i)
using namespace std;
char s[1010];
int m, n;
int main() {
  // freopen("in.txt","r",stdin);
  // freopen("out.txt","w",stdout);
  int T;
  cin >> T;
  rep(cas, 1, T) {
    scanf("%s", s + 1);
    scanf("%d", &m);
    n = strlen(s + 1);
    int ans = 0;
    rep(i, 1, n - m + 1) {
      if (s[i] == '-') {
        ++ans;
        rep(j, 1, m) if (s[i + j - 1] == '+') s[i + j - 1] = '-';
        else s[i + j - 1] = '+';
      }
    }
    bool flag = 1;
    rep(i, 1, n) if (s[i] == '-') flag = 0;
    if (flag)
      printf("Case #%d: %d\n", cas, ans);
    else
      printf("Case #%d: IMPOSSIBLE\n", cas);
  }
}
