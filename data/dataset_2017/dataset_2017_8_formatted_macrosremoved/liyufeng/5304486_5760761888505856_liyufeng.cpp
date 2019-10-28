#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
const int INF = 0x7fffffff;
const long long INFF = 0x7fffffffffffffff;
const double pi = 3.141592653589793;
const double inf = 1e18;
const double eps = 1e-8;
const long long mod = 1e9 + 7;
/*************************************************************/
int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int kase;
  cin >> kase;
  char a[30][30];
  for (int t = 1; t <= kase; t++) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      scanf("%s", &a[i]);
    }
    for (int j = 0; j < m; j++) {
      for (int i = 0; i < n; i++) {
        if (a[i][j] != '?') {
          for (int k = i + 1; k < n; k++) {
            if (a[k][j] == '?')
              a[k][j] = a[i][j];
            else
              break;
          }
          for (int k = i - 1; k >= 0; k--) {
            if (a[k][j] == '?')
              a[k][j] = a[i][j];
            else
              break;
          }
        }
      }
    }
    for (int j = 0; j < m; j++) {
      if (a[0][j] != '?') {
        for (int k = j - 1; k >= 0; k--) {
          if (a[0][k] == '?') {
            for (int i = 0; i < n; i++)
              a[i][k] = a[i][j];
          } else
            break;
        }
        for (int k = j + 1; k < m; k++) {
          if (a[0][k] == '?') {
            for (int i = 0; i < n; i++)
              a[i][k] = a[i][j];
          } else
            break;
        }
      }
    }
    printf("Case #%d:\n", t);
    for (int i = 0; i < n; i++)
      printf("%s\n", a[i]);
  }
  fclose(stdin);
  fclose(stdout);

  return 0;
}
