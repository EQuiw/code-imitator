#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#define eps 1e-8
#define MAXN 100050
using namespace std;
char s[200];
int a[200];
int ans[200];
bool check(int *x, int *y, int n) {
  for (int j = 0; j < n; ++j) {
    if (x[j] == y[j])
      continue;
    if (x[j] < y[j])
      return true;
    return false;
  }
  return true;
}
int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);
  int tt, ri = 0;
  scanf("%d", &tt);
  while (tt--) {
    scanf(" %s", s);
    int n = strlen(s);
    if (n == 1) {
      printf("Case #%d: %s\n", ++ri, s);
      continue;
    }
    for (int i = 0; i < n; ++i)
      a[i] = s[i] - '0';
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j)
        ans[j] = a[i];
      if (check(ans, a, n))
        continue;
      ans[i] = a[i] - 1;
      for (int j = i + 1; j < n; ++j)
        ans[j] = 9;
      break;
    }
    printf("Case #%d: ", ++ri);
    if (ans[0] == 0) {
      for (int i = 1; i < n; ++i)
        printf("%d", ans[i]);
      puts("");
    } else {
      for (int i = 0; i < n; ++i)
        printf("%d", ans[i]);
      puts("");
    }
  }
  return 0;
}
