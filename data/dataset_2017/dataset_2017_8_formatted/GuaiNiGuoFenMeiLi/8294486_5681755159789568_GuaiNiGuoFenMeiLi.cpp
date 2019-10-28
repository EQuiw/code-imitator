#include <stdio.h>

#include <algorithm>
#include <queue>
#include <string.h>
#include <string>
#include <utility>
#include <vector>

using namespace std;

static const int MAX_N = 100;

int N;
double a[MAX_N], v[MAX_N];
double d[MAX_N][MAX_N];
int Q, U, V;

double f[MAX_N];

double solve() {
  for (int i = 0; i < N; ++i) {
    f[i] = 1e18;
  }
  priority_queue<pair<double, int>> PQ;
  f[U] = 0;
  PQ.push(make_pair(-f[U], U));
  while (!PQ.empty()) {
    double cur = -PQ.top().first;
    int s = PQ.top().second;
    PQ.pop();
    for (int t = 0; t < N; ++t) {
      if (d[s][t] >= 0 && d[s][t] <= a[s] && cur + d[s][t] / v[s] < f[t]) {
        f[t] = cur + d[s][t] / v[s];
        PQ.push(make_pair(-f[t], t));
      }
    }
  }
  return f[V];
}

int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-small-attempt0.out", "w", stdout);

  int T;
  scanf("%d", &T);
  for (int test = 1; test <= T; ++test) {
    scanf("%d%d", &N, &Q);
    for (int i = 0; i < N; ++i) {
      scanf("%lf%lf", &a[i], &v[i]);
    }
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        scanf("%lf", &d[i][j]);
      }
    }
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        for (int k = 0; k < N; ++k) {
          if (d[i][k] >= 0 && d[k][j] >= 0 &&
              (d[i][j] < 0 || d[i][j] > d[i][k] + d[k][j])) {
            d[i][j] = d[i][k] + d[k][j];
          }
        }
      }
    }
    printf("Case #%d:", test);
    while (Q--) {
      scanf("%d%d", &U, &V);
      --U;
      --V;
      printf(" %.12lf", solve());
    }
    puts("");
  }

  return 0;
}
