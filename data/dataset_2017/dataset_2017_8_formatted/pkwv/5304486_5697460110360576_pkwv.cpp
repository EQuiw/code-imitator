#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

const int N = 55;

int p[N][N];
int g[N], pnt[N];
pair<int, int> pr[N];

pair<int, int> get_interval(int x, int y) {
  int l = (y * 10 + 11 * x - 1) / (11 * x);
  int r = y * 10 / (9 * x);
  return make_pair(l, r);
}

bool check(int n, int m) {
  for (int i = 0; i < n; i++)
    if (pnt[i] >= m)
      return false;
  return true;
}

void update(pair<int, int> &lr, pair<int, int> v) {
  lr.first = max(lr.first, v.first);
  lr.second = min(lr.second, v.second);
}

int main() {
  freopen("/home/zhangyingzhe/Downloads/B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int ca = 1; ca <= T; ca++) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
      scanf("%d", &g[i]);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++)
        scanf("%d", &p[i][j]);
      sort(p[i], p[i] + m);
    }
    for (int i = 0; i < n; i++)
      pnt[i] = 0;
    int res(0);
    while (check(n, m)) {
      int sl(-1);
      pair<int, int> lr = make_pair(INT_MIN, INT_MAX);
      for (int i = 0; i < n; i++) {
        pr[i] = get_interval(g[i], p[i][pnt[i]]);
        // printf("~~~%d  %d  %d\n",i, pr[i].first, pr[i].second);
        if (sl == -1 || pr[i].second < pr[sl].second)
          sl = i;
        update(lr, pr[i]);
      }
      if (lr.second >= lr.first) {
        ++res;
        for (int i = 0; i < n; i++)
          ++pnt[i];
      } else {
        ++pnt[sl];
      }
    }
    printf("Case #%d: %d\n", ca, res);
  }
  return 0;
}