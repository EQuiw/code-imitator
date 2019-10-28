#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
  freopen("123.in", "r", stdin);
  freopen("123.out", "w", stdout);
  int T, cas = 0;
  cin >> T;
  while (T --) {
    string s;
    int k, ans = 0;
    cin >> s >> k;
    for (int i = 0; i + k <= s.size(); i ++) {
      if (s[i] == '-') {
        for (int j = 0; j < k; j ++)
          s[i + j] = s[i + j] == '-' ? '+' : '-';
        ans ++;
      }
    }
    printf("Case #%d: ", ++ cas);
    if (s == string(s.size(), '+'))
      printf("%d\n", ans);
    else
      puts("IMPOSSIBLE");
  }
  return 0;
}