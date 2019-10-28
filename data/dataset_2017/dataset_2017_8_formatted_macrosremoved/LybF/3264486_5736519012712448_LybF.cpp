#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.0);

int solve(char *s, int k) {
  int ret = 0;
  int n = (int)strlen(s);
  for (int i = 0; i + k <= n; i++) {
    if (s[i] == '-') {
      ret++;
      for (int j = 0; j < k; j++) {
        s[i + j] = (s[i + j] == '+') ? '-' : '+';
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (s[i] == '-') {
      return 0x3f3f3f3f;
    }
  }
  return ret;
}

int main() {
  //    freopen("in.txt","r",stdin);
  freopen("out.txt", "w", stdout);

  int T;
  scanf("%d", &T);

  for (int cas = 1; cas <= T; cas++) {
    char s[1005];
    char p[1005];
    int k;
    scanf("%s %d", s, &k);
    int n = strlen(s);
    strcpy(p, s);
    int first = solve(p, k);

    strcpy(p, s);
    for (int i = 0, j = n - 1; i <= j; i++, j--) {
      swap(p[i], p[j]);
    }
    int second = solve(p, k);

    int ret = min(first, second);

    if (ret != 0x3f3f3f3f) {
      printf("Case #%d: %d\n", cas, ret);
    } else {
      printf("Case #%d: IMPOSSIBLE\n", cas);
    }
  }
  return 0;
}
