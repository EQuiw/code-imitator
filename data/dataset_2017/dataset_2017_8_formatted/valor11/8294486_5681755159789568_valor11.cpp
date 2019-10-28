#include <bits/stdc++.h>

using namespace std;
const int N = 123;
double a[N][N];
double e[N], s[N];
double f[N][N];
bool v[N];
int n, q;

void spfa(int st) {
  queue<int> q;
  memset(v, 0, sizeof(v));
  q.push(st);

  v[st] = 1;

  auto max_dis = e[st];

  while (!q.empty()) {
    int x = q.front();
    q.pop();

    for (int i = 0; i < n; i++) {
      if (a[x][i] != -1) {
        auto dis = f[st][x] + a[x][i];
        if (dis <= max_dis && (dis < f[st][i])) {
          f[st][i] = dis;
          if (!v[i]) {
            v[i] = 1;
            q.push(i);
          }
        }
      }
    }

    v[x] = 0;
  }

  for (int i = 0; i < n; i++)
    if (f[st][i] < 1e12)
      f[st][i] /= s[st];
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; cas++) {
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
      scanf("%lf%lf", e + i, s + i);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%lf", &a[i][j]);
        f[i][j] = 1e20;
      }
      f[i][i] = 0;
    }

    for (int i = 0; i < n; i++)
      spfa(i);

    //*
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        printf("%.6f ", f[i][j]);
      puts("");
    }
    //*/
    // floyed
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++)
        if (i != k) {
          for (int j = 0; j < n; j++)
            if (i != j && j != k) {
              if (f[i][k] + f[k][j] < f[i][j]) {
                f[i][j] = f[i][k] + f[k][j];
              }
            }
        }
    }

    int x, y;
    printf("Case #%d:", cas);
    while (q--) {
      scanf("%d%d", &x, &y);
      x--;
      y--;
      printf(" %.7f", f[x][y]);
    }
    puts("");
  }
  return 0;
}