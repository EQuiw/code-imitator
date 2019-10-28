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
int n;
int pn;
int re[55];
int dat[55][55];

typedef pair<mp, int> mmp;
int solve() {
  priority_queue<mmp> que;
  for (int i = 0; i < ((int)(n)); i++)
    for (int j = 0; j < ((int)(pn)); j++) {
      int x = dat[i][j];
      int t = re[i];
      // printf("%d %d\n",x,t);
      int r = (x * 10 + 11 * t - 1) / (11 * t);
      int l = (10 * x) / (9 * t);
      if (l < r)
        continue;
      que.push(mmp(mp(r, -1), i));
      que.push(mmp(mp(l, 1), i));
    }

  int res = 0;
  int dn[55];
  memset(dn, 0, sizeof(dn));
  while (!que.empty()) {
    mmp pa = que.top();
    que.pop();
    int ty = pa.first.second, ni = pa.second;

    dn[ni] += ty;
    // printf("t %d ty %d i %d\n",pa.fir.fir,ty,ni);
    dn[ni] = max(dn[ni], 0);
    int ng = 100;
    for (int i = 0; i < ((int)(n)); i++) {
      ng = min(ng, dn[i]);
    }
    // printf("%d %d\n",pn,ng);
    res += ng;
    for (int i = 0; i < ((int)(n)); i++)
      dn[i] -= ng;
  }
  return res;
}

int main(void) {
  int qn;
  scanf("%d", &qn);
  for (int qqq = ((int)(1)); qqq <= ((int)(qn)); qqq++) {
    scanf("%d%d", &n, &pn);
    for (int i = 0; i < ((int)(n)); i++)
      scanf("%d", &re[i]);
    for (int i = 0; i < ((int)(n)); i++)
      for (int j = 0; j < ((int)(pn)); j++)
        scanf("%d", &dat[i][j]);
    printf("Case #%d: %d\n", qqq, solve());
  }
  return 0;
}
