#include <algorithm>
#include <map>
#include <math.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int n, m;
int a[50], w[50][50], p[50];
int l[50], r[50];

int solve() {
  int ans = 0;
  while (true) {
    for (int i = 0; i < n; ++i) {
      if (p[i] == m) {
        return ans;
      }
    }

    int L = 0, R = (int)1e9;
    int ml = (int)1e9, nxt = -1;
    bool flag = false;
    for (int i = 0; i < n; ++i) {
      // w[i][p[i]]
      // x * a[i] * 0.9 <= w[i][p[i]] <= x * a[i] * 1.1
      l[i] = (w[i][p[i]] * 10 + a[i] * 11 - 1) / (a[i] * 11);
      r[i] = (w[i][p[i]] * 10) / (a[i] * 9);
      if (l[i] > r[i]) {
        p[i]++;
        flag = true;
        break;
      }
      if (ml > l[i]) {
        ml = l[i];
        nxt = i;
      }
      L = max(L, l[i]);
      R = min(R, r[i]);
    }
    if (flag) {
      continue;
    }
    if (L <= R) {
      ans++;
      for (int j = 0; j < n; ++j) {
        p[j]++;
      }
    } else {
      p[nxt]++;
    }
  }
}

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);

  int T;
  scanf("%d", &T);
  for (int test = 1; test <= T; ++test) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", &w[i][j]);
      }
      sort(w[i], w[i] + m);
      p[i] = 0;
    }
    int ans = solve();

    printf("Case #%d: %d\n", test, ans);
  }

  return 0;
}
