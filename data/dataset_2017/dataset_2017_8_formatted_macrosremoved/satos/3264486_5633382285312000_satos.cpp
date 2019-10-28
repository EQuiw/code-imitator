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
char s[20];

lli solve() {
  scanf("%s", s);
  int ls = strlen(s);
  for (;;) {
    bool ok = true;
    for (int i = 0; i < ((int)(ls - 1)); i++) {
      if (s[i] > s[i + 1]) {
        ok = false;
        s[i] -= 1;
        for (int j = ((int)(i + 1)); j <= ((int)(ls - 1)); j++) {
          s[j] = '9';
        }
        break;
      }
    }
    if (ok)
      break;
  }

  lli res = 0;
  for (int i = 0; i < ((int)(ls)); i++) {
    res *= 10;
    res += s[i] - '0';
  }
  return res;
}

int main(void) {
  int qn;
  scanf("%d", &qn);
  for (int qqq = ((int)(1)); qqq <= ((int)(qn)); qqq++) {
    lli x = solve();
    printf("Case #%d: %lld\n", qqq, x);
  }
  return 0;
}
