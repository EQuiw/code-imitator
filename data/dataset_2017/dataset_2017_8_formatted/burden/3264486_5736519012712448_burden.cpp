#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int Maxn = 2000;
int n, k;
char s[Maxn];

int main() {
  // freopen("a.in","r",stdin);
  // freopen("a.out","w",stdout);
  int T, w = 0;
  for (scanf("%d", &T); T--;) {
    scanf("%s%d", s + 1, &k);
    printf("Case #%d: ", ++w);
    n = strlen(s + 1);
    int ans = 0;
    for (int i = 1; i <= n - k + 1; i++)
      if (s[i] == '-') {
        for (int j = i; j <= i + k - 1; j++)
          s[j] = (s[j] == '-') ? '+' : '-';
        ans++;
      }
    bool flag = true;
    for (int i = 1; i <= n; i++)
      if (s[i] == '-')
        flag = false;
    if (flag)
      printf("%d\n", ans);
    else
      printf("IMPOSSIBLE\n");
  }
  return 0;
}
