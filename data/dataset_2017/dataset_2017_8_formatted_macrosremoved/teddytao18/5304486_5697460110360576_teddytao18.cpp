#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

int h[60];
int l[60][60];
int r[60][60];
int q[60][60];
int curr[60];

struct cmp {
  bool operator()(int a, int b) { return r[a][curr[a]] > r[b][curr[b]]; }
};

priority_queue<int, vector<int>, cmp> pq;

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    int i, j, n, p, y, ans, xl, xr;
    scanf("%d %d", &n, &p);
    for (i = 0; i < n; i++)
      scanf("%d", &h[i]);
    for (i = 0; i < n; i++) {
      for (j = 0; j < p; j++)
        scanf("%d", &q[i][j]);
      sort(q[i], q[i] + p);
    }
    for (i = 0; i < n; i++)
      for (j = 0; j < p; j++) {
        l[i][j] = ceil((double)q[i][j] / h[i] / 1.1);
        r[i][j] = (double)q[i][j] / h[i] / 0.9;
      }
    /*
    for (i=0;i<n;i++)
    {
        for (j=0;j<p;j++)
            printf("[%d,%d] ",l[i][j],r[i][j]);
        printf("\n");
    }
    */
    memset(curr, 0, sizeof(curr));
    for (i = 0; i < n; i++)
      pq.push(i);
    /*
       while (!pq.empty())
       {
       int tmp=pq.top();
       printf("%d %d\n",tmp,r[tmp][curr[tmp]]);
       pq.pop();
       }
     */
    ans = 0;
    while (1) {
      xl = 0;
      xr = 0x7f7f7f7f;
      for (i = 0; i < n; i++) {
        xl = max(xl, l[i][curr[i]]);
        xr = min(xr, r[i][curr[i]]);
      }
      if (xl > xr) {
        y = pq.top();
        pq.pop();
        curr[y]++;
        if (curr[y] == p)
          break;
        pq.push(y);
      } else {
        ans++;
        while (!pq.empty())
          pq.pop();
        for (i = 0; i < n; i++) {
          curr[i]++;
          if (curr[i] == p)
            break;
        }
        if (i != n)
          break;
        for (i = 0; i < n; i++)
          pq.push(i);
      }
    }

    printf("Case #%d: %d\n", t, ans);
  }
}
