#include <bits/stdc++.h>

using namespace std;

char a[77][77];

int main() {
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
  int tt;
  scanf("%d", &tt);
  for (int cc = 1; cc <= tt; ++cc) {
    double begt = clock();
    printf("Case #%d:\n", cc);
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
      scanf("%s", a[i]);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m - 1; ++j) {
        if (a[i][j] != '?' && a[i][j + 1] == '?') {
          a[i][j + 1] = a[i][j];
        }
      }
      for (int j = m - 1; j > 0; --j) {
        if (a[i][j] != '?' && a[i][j - 1] == '?') {
          a[i][j - 1] = a[i][j];
        }
      }
    }
    for (int i = 0; i < n - 1; ++i) {
      for (int j = 0; j < m; ++j) {
        if (a[i][j] != '?' && a[i + 1][j] == '?') {
          a[i + 1][j] = a[i][j];
        }
      }
    }
    for (int i = n - 1; i > 0; --i) {
      for (int j = 0; j < m; ++j) {
        if (a[i][j] != '?' && a[i - 1][j] == '?') {
          a[i - 1][j] = a[i][j];
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      printf("%s\n", a[i]);
    }
    fprintf(stderr, "case %d solved in %.3f\n", cc, (clock() - begt) / CLOCKS_PER_SEC);
  }
}