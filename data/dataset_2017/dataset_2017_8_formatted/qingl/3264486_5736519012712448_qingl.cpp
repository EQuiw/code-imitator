#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1005;
char str[N];
int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  int T, ca = 1, k;
  scanf("%d", &T);
  while (T--) {
    printf("Case #%d: ", ca++);
    scanf("%s%d", str, &k);
    int n = strlen(str), ret = 0;
    for (int i = 0; i < n - k + 1; i++) {
      if (str[i] == '-') {
        for (int j = 0; j < k; j++) {
          str[i + j] = str[i + j] == '+' ? '-' : '+';
        }
        ret++;
      }
    }
    for (int i = 0; i < n; i++) {
      if (str[i] == '-')
        ret = -1;
    }
    if (ret == -1)
      puts("IMPOSSIBLE");
    else
      printf("%d\n", ret);
  }
  return 0;
}
