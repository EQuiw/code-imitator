// Problem B

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int get() {
  char c;
  while (c = getchar(), c != '-' && (c < '0' || c > '9'))
    ;
  bool flag = (c == '-');
  if (flag)
    c = getchar();
  int x = 0;
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return flag ? -x : x;
}

int a[1000], p[1000];
double x[1000][1000], lb[1000][1000], ub[1000][1000];

int main() {
  int totalTest = get();
  for (int test = 1; test <= totalTest; test++) {
    int n = get(), m = get();
    for (int i = 0; i < n; i++)
      a[i] = get();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        x[i][j] = (double)get() / a[i];
      }
      sort(x[i], x[i] + m);
      for (int j = 0; j < m; j++) {
        lb[i][j] = ceil(x[i][j] / 1.1);
        ub[i][j] = floor(x[i][j] / 0.9);
      }
    }
    int ans = 0;
    memset(p, 0, sizeof(p));
    for (int i = 0; i < m; i++) {
      if (lb[0][i] > ub[0][i])
        continue;
      bool flag = true;
      for (int j = 1; j < n; j++) {
        while (p[j] < m && ub[j][p[j]] < lb[0][i])
          p[j]++;
        flag = (p[j] < m) && (lb[j][p[j]] <= ub[0][i]);
      }
      if (flag) {
        ans++;
        for (int j = 1; j < n; j++)
          p[j]++;
      }
    }
    printf("Case #%d: %d\n", test, ans);
  }
  return 0;
}
