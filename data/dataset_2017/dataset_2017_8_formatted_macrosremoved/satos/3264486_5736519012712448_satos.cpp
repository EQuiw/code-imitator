#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef long long int lli;
typedef pair<int, int> mp;
char s[1005];
int solve() {
  int k;
  scanf("%s%d", s, &k);
  int ls = strlen(s);
  for (int i = 0; i < ((int)(ls)); i++) {
    s[i] = (s[i] == '+' ? 1 : 0);
  }

  int res = 0;
  for (int i = 0; i < ((int)(ls)); i++) {
    if (s[i] == 0) {
      if (i + k - 1 >= ls)
        return -1;
      res++;
      for (int j = ((int)(i)); j <= ((int)(min(ls - 1, i + k - 1))); j++) {
        s[j] = 1 - s[j];
      }
    }
  }
  return res;
}

int main(void) {
  int qn;
  scanf("%d", &qn);
  for (int qqq = ((int)(1)); qqq <= ((int)(qn)); qqq++) {
    int x = solve();
    if (x >= 0)
      printf("Case #%d: %d\n", qqq, x);
    else
      printf("Case #%d: IMPOSSIBLE\n", qqq);
  }
  return 0;
}
