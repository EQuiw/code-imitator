#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int Maxn = 50;
int n;
char s[Maxn];

bool Check(int t) {
  for (int i = 2; i <= t; i++)
    if (s[i] < s[i - 1])
      return false;
  return true;
}

int main() {
  // freopen("b.in","r",stdin);
  // freopen("b.out","w",stdout);
  int T, w = 0;
  for (scanf("%d", &T); T--;) {
    scanf("%s", s + 1);
    printf("Case #%d: ", ++w);
    n = strlen(s + 1);
    if (Check(n)) {
      printf("%s\n", s + 1);
      continue;
    }
    for (int i = n; i > 0; i--)
      if (s[i] != '0') {
        s[i] = s[i] - 1;
        if (Check(i)) {
          int k = 1;
          while (s[k] == '0')
            k++;
          for (int j = k; j <= i; j++)
            printf("%c", s[j]);
          for (int j = i + 1; j <= n; j++)
            printf("9");
          printf("\n");
          break;
        }
        s[i] = s[i] + 1;
      }
  }
  return 0;
}
