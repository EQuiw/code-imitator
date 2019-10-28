#include <cstdio>
#include <cstring>
using namespace std;
char s[1010];
int k, l;
bool flag;
inline void solve() {
  int cnt = 0;
  scanf("%s%d", s, &k);
  l = strlen(s);
  for (int i = 0; i + k - 1 < l; i++) {
    if (s[i] == '-') {
      for (int j = i; j < i + k; j++)
        if (s[j] == '-')
          s[j] = '+';
        else
          s[j] = '-';
      cnt++;
    }
  }
  flag = true;
  for (int i = 0; i < l; i++)
    if (s[i] == '-') {
      flag = false;
      break;
    }
  if (flag)
    printf("%d\n", cnt);
  else
    printf("IMPOSSIBLE\n");
}
int main() {
  // freopen("in.txt","r",stdin);
  // freopen("out.txt","w",stdout);
  int T;
  scanf("%d", &T);
  for (int tcase = 1; tcase <= T; tcase++) {
    printf("Case #%d: ", tcase);
    solve();
  }
  return 0;
}