#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int Case, k, len;
char s[1000 + 5];
bool Flag[1000 + 5];

int main() {
  scanf("%d", &Case);
  for (int T = 1; T <= Case; T++) {
    printf("Case #%d: ", T);
    scanf("%s%d", s, &k);
    len = strlen(s);
    for (int i = 0; i < len; i++)
      Flag[i] = 0;
    int step = 0;
    for (int i = 0, del = 0; ~step && i < len; i++) {
      del ^= Flag[i];
      int t = (s[i] == '-');
      if (del ^ t) {
        if (i + k > len)
          step = -1;
        else
          Flag[i + 1] ^= 1, Flag[i + k] ^= 1, step++;
      }
    }
    if (!~step)
      puts("IMPOSSIBLE");
    else
      printf("%d\n", step);
  }
  return 0;
}
