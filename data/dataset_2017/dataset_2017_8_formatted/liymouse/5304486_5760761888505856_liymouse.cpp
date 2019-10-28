#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef long long i64d;

using namespace std;

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int cas;
  scanf("%d", &cas);
  for (int ca = 1; ca <= cas; ca++) {
    printf("Case #%d:\n", ca);
    int r, c;
    scanf("%d %d", &r, &c);
    char s[30][30];
    for (int i = 0; i < r; i++)
      scanf("%s", s[i]);
    for (int i = 0; i < r; i++) {
      int j = 0;
      int last = 0;
      char x = s[i][0];
      while (j < c) {
        while (s[i][j] == '?' && j < c)
          j++;
        if (j < c) {
          for (int k = last; k < j; k++)
            s[i][k] = s[i][j];
          x = s[i][j];
          j++;
          last = j;
        }
      }
      if (last < c) {
        for (int j = last; j < c; j++)
          s[i][j] = x;
      }
    }
    for (int i = 1; i < r; i++)
      if (s[i][0] == '?') // black line
      {
        for (int j = 0; j < c; j++)
          s[i][j] = s[i - 1][j];
      }
    for (int i = r - 1; i >= 0; i--)
      if (s[i][0] == '?') {
        for (int j = 0; j < c; j++)
          s[i][j] = s[i + 1][j];
      }
    for (int i = 0; i < r; i++)
      printf("%s\n", s[i]);
  }
  return 0;
}