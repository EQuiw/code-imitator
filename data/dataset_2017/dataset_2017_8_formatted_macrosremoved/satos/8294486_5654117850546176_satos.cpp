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
#include <cassert>

int sn;
int d[10];

char ans[1005];

const char *ass[7] = {"", "R", "Y", "BO", "B", "VY", "GR"};

int solve() {
  int tb[3] = {3, 5, 6};
  // reg(i,1,6)printf("%d ",d[i]); puts("");
  for (int i = 0; i < ((int)(3)); i++) {
    int x = tb[i], a = d[x];
    // printf("%d %d %d\n",x,a,d[7-x]);
    if (a > 0) {
      if (d[7 - x] < a + 1) {
        for (int j = ((int)(1)); j <= ((int)(6)); j++) {
          if (j == x || j == 7 - x)
            continue;
          if (d[j] != 0)
            return 0;
        }
        if (d[7 - x] == a) {
          sn = 0;
          for (int j = 0; j < ((int)(a)); j++) {
            printf("%s", ass[x]);
          }
          puts("");
          return -1;
        }
        return 0;
      }
      d[7 - x] -= a + 1;
      sn -= 2 * a;
    }
  }

  mp ps[3];
  for (int i = 0; i < ((int)(3)); i++) {
    int p = 1 << i;
    int t = d[p] + (d[7 - p] ? 1 : 0);
    // printf("pd[%d] %d\n",i,t);
    if (t * 2 > sn)
      return 0;
    ps[i] = mp(t, i);
  }

  sort(ps, ps + 3, greater<mp>());

  for (int i = 0; i < ((int)(sn)); i++) {
    ans[i] = ps[2].second;
  }
  int np = 0;
  for (int i = 0; i < ((int)(ps[0].first)); i++) {
    ans[np] = ps[0].second;
    np += 2;
  }

  np = (np - 1 + sn) % sn;
  for (int i = 0; i < ((int)(ps[1].first)); i++) {
    assert(ans[np] == ps[2].second);
    ans[np] = ps[1].second;
    if (np + 2 < sn)
      np += 2;
    else
      np = 1;
  }

  /*
  printf("sn %d\n",sn);
  rep(i,sn)printf("%d ",ans[i]);
  puts("");
  */

  return 1;
}

int main(void) {
  int qn;
  scanf("%d", &qn);
  int ds[6] = {1, 3, 2, 6, 4, 5};
  for (int qqq = ((int)(1)); qqq <= ((int)(qn)); qqq++) {
    scanf("%d", &sn);
    for (int i = 0; i < ((int)(6)); i++) {
      int x;
      scanf("%d", &x);
      d[ds[i]] = x;
    }
    printf("Case #%d: ", qqq);
    int t = solve();
    if (t == 1) {
      for (int i = 0; i < ((int)(sn)); i++) {
        int x = 1 << ans[i];
        if (d[x] <= 0) {
          x = 7 - x;
          assert(d[x] > 0);
          printf("%s", ass[7 - x]);
          for (int i = 0; i < ((int)(d[x])); i++) {
            printf("%s", ass[x]);
          }
          d[x] = 0;
        } else {
          printf("%s", ass[x]);
          d[x]--;
        }
      }
      puts("");
    } else if (t == 0)
      puts("IMPOSSIBLE");
    else
      continue;
  }
  return 0;
}
