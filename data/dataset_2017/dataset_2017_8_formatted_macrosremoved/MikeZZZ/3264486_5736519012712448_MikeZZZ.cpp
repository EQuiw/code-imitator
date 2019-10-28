#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1000 + 5;
int T, Case, n, k;
char s[N];

int main() {
  // freopen("out.out","w",stdout);
  // freopen("A-small-attempt0.in","r",stdin);
  scanf("%d", &T);
  while (T--) {
    scanf("%s%d", s, &k);
    n = strlen(s);
    int ans = 0;
    for (int i = 0; i <= n - k; i++) {
      if (s[i] == '-') {
        ans++;
        for (int j = i; j < i + k; j++)
          s[j] = '+' + '-' - s[j];
      }
    }
    int flag = 1;
    for (int i = n - k + 1; i < n; i++) {
      if (s[i] == '-')
        flag = 0;
    }
    printf("Case #%d: ", ++Case);
    if (!flag)
      puts("IMPOSSIBLE");
    else
      printf("%d\n", ans);
  }
  return 0;
}
