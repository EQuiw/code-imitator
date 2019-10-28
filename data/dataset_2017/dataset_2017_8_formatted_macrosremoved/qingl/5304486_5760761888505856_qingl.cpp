#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 105;
char s[N][N];
int main() {
  freopen("A-small-attempt1.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  int T, ca = 1;
  scanf("%d", &T);
  while (T--) {
    printf("Case #%d:\n", ca++);
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++) {
      scanf("%s", s[i]);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (s[j][i] != '?') {
          int k = j - 1;
          while (k >= 0 && s[k][i] == '?') {
            s[k][i] = s[j][i];
            k--;
          }
          k = j + 1;
          while (k < m && s[k][i] == '?') {
            s[k][i] = s[j][i];
            k++;
          }
        }
      }
    }
    for (int i = 1; i < n; i++) {
      for (int j = 0; j < m; j++)
        if (s[j][i] == '?') {
          s[j][i] = s[j][i - 1];
        }
    }
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 0; j < m; j++)
        if (s[j][i] == '?') {
          if (i < n - 1)
            s[j][i] = s[j][i + 1];
        }
    }
    for (int i = 0; i < m; i++)
      puts(s[i]);
  }
  return 0;
}
