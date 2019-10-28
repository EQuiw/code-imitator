// Problem C

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

const double inf = 1e15;

double l[100], v[100];
double dist[100][100];
double g[100][100];

int main() {
  int totalTest = get();
  for (int test = 1; test <= totalTest; test++) {
    int n = get(), q = get();
    for (int i = 0; i < n; i++) {
      l[i] = get();
      v[i] = get();
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        int x = get();
        if (i == j)
          dist[i][j] = 0;
        else
          dist[i][j] = (x == -1) ? inf : x;
      }
    for (int k = 0; k < n; k++)
      for (int i = 0; i < n; i++)
        if (dist[i][k] < inf)
          for (int j = 0; j < n; j++)
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        g[i][j] = (dist[i][j] <= l[i]) ? (dist[i][j] / v[i]) : inf;
    for (int k = 0; k < n; k++)
      for (int i = 0; i < n; i++)
        if (g[i][k] < inf)
          for (int j = 0; j < n; j++)
            g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
    printf("Case #%d:", test);
    for (int i = 0; i < q; i++) {
      int u = get() - 1, v = get() - 1;
      printf(" %0.10lf", g[u][v]);
    }
    putchar('\n');
  }
  return 0;
}
