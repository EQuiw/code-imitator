#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef long long int lli;
typedef pair<int, int> mp;
int h, w;
char s[30][30];
void solve() {
  for (int c = ((int)('A')); c <= ((int)('z')); c++) {
    if (c > 'Z' && c <= 'a')
      continue;
    int u = 100, d = -1, l = 100, r = -1;
    for (int y = 0; y < ((int)(h)); y++) {
      for (int x = 0; x < ((int)(w)); x++) {
        if (s[y][x] == c) {
          u = min(u, y);
          d = max(d, y);
          l = min(l, x);
          r = max(r, x);
        }
      }
    }

    for (int y = ((int)(u)); y <= ((int)(d)); y++)
      for (int x = ((int)(l)); x <= ((int)(r)); x++) {
        s[y][x] = c;
      }
  }

  for (int y = 0; y < ((int)(h)); y++) {
    int ox = -1;
    for (int x = 0; x < ((int)(w)); x++) {
      if (s[y][x] != '?') {
        ox = x;
        break;
      }
    }
    if (ox >= 0) {
      for (int x = 0; x < ((int)(ox)); x++)
        s[y][x] = s[y][ox];
      char nc = s[y][ox];
      for (int x = ((int)(ox)); x <= ((int)(w - 1)); x++) {
        if (s[y][x] == '?') {
          s[y][x] = nc;
        } else
          nc = s[y][x];
      }
    }
  }
  for (int y = ((int)(1)); y <= ((int)(h - 1)); y++) {
    if (s[y][0] != '?')
      continue;
    if (s[y - 1][0] == '?')
      continue;
    for (int x = 0; x < ((int)(w)); x++) {
      s[y][x] = s[y - 1][x];
    }
  }
  for (int y = ((int)(h - 2)); y >= ((int)(0)); y--) {
    if (s[y][0] != '?')
      continue;
    if (s[y + 1][0] == '?')
      continue;
    for (int x = 0; x < ((int)(w)); x++) {
      s[y][x] = s[y + 1][x];
    }
  }
}

int main(void) {
  int qn;
  scanf("%d", &qn);
  for (int qqq = ((int)(1)); qqq <= ((int)(qn)); qqq++) {
    scanf("%d%d", &h, &w);
    for (int y = 0; y < ((int)(h)); y++)
      scanf("%s", s[y]);
    solve();
    printf("Case #%d:\n", qqq);
    for (int y = 0; y < ((int)(h)); y++) {
      puts(s[y]);
    }
  }
  return 0;
}
