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
#define rep(i, n) for (int i = 0; i < ((int)(n)); i++)
#define reg(i, a, b) for (int i = ((int)(a)); i <= ((int)(b)); i++)
#define irep(i, n) for (int i = ((int)(n)) - 1; i >= 0; i--)
#define ireg(i, a, b) for (int i = ((int)(b)); i >= ((int)(a)); i--)
typedef long long int lli;
typedef pair<int, int> mp;
#define fir first
#define sec second
#define IINF INT_MAX
#define LINF LLONG_MAX
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define pque(type) priority_queue<type, vector<type>, greater<type>>
#define memst(a, b) memset(a, b, sizeof(a))
#define iter(v, ite) for (auto ite = (v).begin(); ite != (v).end(); ite++)
#define mimunum(v, x)                                                          \
  distance((v).begin(), lower_bound((v).begin(), (v).end(), x))

#include <cassert>

int sn;
int d[10];

char ans[1005];

const char *ass[7] = {"", "R", "Y", "BO", "B", "VY", "GR"};

int solve() {
  int tb[3] = {3, 5, 6};
  // reg(i,1,6)printf("%d ",d[i]); puts("");
  rep(i, 3) {
    int x = tb[i], a = d[x];
    // printf("%d %d %d\n",x,a,d[7-x]);
    if (a > 0) {
      if (d[7 - x] < a + 1) {
        reg(j, 1, 6) {
          if (j == x || j == 7 - x)
            continue;
          if (d[j] != 0)
            return 0;
        }
        if (d[7 - x] == a) {
          sn = 0;
          rep(j, a) { printf("%s", ass[x]); }
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
  rep(i, 3) {
    int p = 1 << i;
    int t = d[p] + (d[7 - p] ? 1 : 0);
    // printf("pd[%d] %d\n",i,t);
    if (t * 2 > sn)
      return 0;
    ps[i] = mp(t, i);
  }

  sort(ps, ps + 3, greater<mp>());

  rep(i, sn) { ans[i] = ps[2].sec; }
  int np = 0;
  rep(i, ps[0].fir) {
    ans[np] = ps[0].sec;
    np += 2;
  }

  np = (np - 1 + sn) % sn;
  rep(i, ps[1].fir) {
    assert(ans[np] == ps[2].sec);
    ans[np] = ps[1].sec;
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
  reg(qqq, 1, qn) {
    scanf("%d", &sn);
    rep(i, 6) {
      int x;
      scanf("%d", &x);
      d[ds[i]] = x;
    }
    printf("Case #%d: ", qqq);
    int t = solve();
    if (t == 1) {
      rep(i, sn) {
        int x = 1 << ans[i];
        if (d[x] <= 0) {
          x = 7 - x;
          assert(d[x] > 0);
          printf("%s", ass[7 - x]);
          rep(i, d[x]) { printf("%s", ass[x]); }
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
