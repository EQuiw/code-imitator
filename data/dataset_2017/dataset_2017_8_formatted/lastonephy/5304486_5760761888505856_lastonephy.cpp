#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define LL long long
#define eps 1e-8
#define mem(a, b) memset(a, b, sizeof(a))
#define zero(x) ((x > +eps) - (x < -eps))
#define MAX 100010
using namespace std;
// freopen("", "r", stdin);
// freopen("", "w", stdout);
// printf("Case #%d: ", ii);

char str[30][30];
int num[30];

int main() {
  freopen("A-small-attempt2.in", "r", stdin);
  freopen("A-small-attempt2.out", "w", stdout);
  int t;
  int n, m;
  scanf("%d", &t);
  for (int ii = 1; ii <= t; ii++) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
      scanf("%s", str[i]);
    }
    mem(num, 0);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (str[i][j] != '?') {
          num[str[i][j] - 'A'] = 1;
          for (int k = j - 1; k >= 0; k--) {
            if (str[i][k] != '?') {
              break;
            }
            str[i][k] = str[i][j];
          }
          for (int k = j + 1; k < m; k++) {
            if (str[i][k] != '?') {
              break;
            }
            str[i][k] = str[i][j];
          }
        }
      }
    }
    for (int i = 1; i < n; i++) {
      if (str[i][0] == '?') {
        for (int j = 0; j < m; j++) {
          str[i][j] = str[i - 1][j];
        }
      }
    }
    for (int i = n - 2; i >= 0; i--) {
      if (str[i][0] == '?') {
        for (int j = 0; j < m; j++) {
          str[i][j] = str[i + 1][j];
        }
      }
    }
    printf("Case #%d:\n", ii);
    for (int i = 0; i < n; i++) {
      printf("%s\n", str[i]);
    }
  }
  return 0;
}