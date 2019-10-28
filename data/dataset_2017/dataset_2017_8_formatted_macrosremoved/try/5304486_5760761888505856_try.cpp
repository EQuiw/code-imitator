#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

struct Rectangle {
  char ch;
  int sx;
  int sy;
  int ex;
  int ey;
  Rectangle() {}
  Rectangle(char a, int b, int c, int d, int e) {
    ch = a;
    sx = b;
    sy = c;
    ex = d;
    ey = e;
  }
};

Rectangle r[26 + 1];
char s[25 + 1][25 + 1];
int n, m, k;

bool operator<(const Rectangle &a, const Rectangle &b) {
  return a.sx < b.sx || (a.sx == b.sx && a.sy < b.sy);
}

bool intersect(const Rectangle &a, const Rectangle &b) {
  return !(a.ex < b.sx || a.sx > b.ex || a.ey < b.sy || a.sy > b.ey) &&
         !(a.sx > b.sx && a.ex < b.ex && a.sy > b.sy && a.ey < b.ey);
}

bool intersect(const Rectangle &a, int p) {
  int i;
  for (i = k; i < 26; i++) {
    if ((i != p) && (intersect(a, r[i]) == true)) {
      return true;
    }
  }
  return false;
}

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int c, t, i, j, x, y;
  scanf("%d", &t);
  for (c = 0; c < t; c++) {
    memset(r, -1, sizeof(r));
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; i++) {
      scanf("%s", s[i]);
      for (j = 0; j < m; j++) {
        if (isupper(s[i][j])) {
          k = (int)(s[i][j] - 'A');
          if ((r[k].sx == -1) && (r[k].ex == -1) && (r[k].sy == -1) &&
              (r[k].ey == -1)) {
            r[k].ch = s[i][j];
            r[k].sx = i;
            r[k].sy = j;
            r[k].ex = i;
            r[k].ey = j;
          } else {
            r[k].sx = min(r[k].sx, i);
            r[k].sy = min(r[k].sy, j);
            r[k].ex = max(r[k].ex, i);
            r[k].ey = max(r[k].ey, j);
          }
        }
      }
    }
    sort(r, r + 26);
    for (k = 0; k < 26; k++) {
      if ((r[k].sx != -1) && (r[k].sy != -1) && (r[k].ex != -1) &&
          (r[k].ey != -1)) {
        break;
      }
    }
    for (i = k; i < 26; i++) {
      while (
          (r[i].sx - 1 >= 0) &&
          (intersect(Rectangle(r[i].ch, r[i].sx - 1, r[i].sy, r[i].ex, r[i].ey),
                     i) == false)) {
        r[i].sx--;
      }
      while (
          (r[i].sy - 1 >= 0) &&
          (intersect(Rectangle(r[i].ch, r[i].sx, r[i].sy - 1, r[i].ex, r[i].ey),
                     i) == false)) {
        r[i].sy--;
      }
      while ((r[i].ex + 1 < n) &&
             (intersect(Rectangle(r[i].ch, r[i].sx + 1, r[i].sy, r[i].ex + 1,
                                  r[i].ey),
                        i) == false)) {
        r[i].ex++;
      }
      while (
          (r[i].ey + 1 < m) &&
          (intersect(Rectangle(r[i].ch, r[i].sx, r[i].sy, r[i].ex, r[i].ey + 1),
                     i) == false)) {
        r[i].ey++;
      }
    }
    for (i = k; i < 26; i++) {
      for (x = r[i].sx; x <= r[i].ex; x++) {
        for (y = r[i].sy; y <= r[i].ey; y++) {
          s[x][y] = r[i].ch;
        }
      }
    }
    printf("Case #%d:\n", c + 1);
    for (i = 0; i < n; i++) {
      printf("%s\n", s[i]);
    }
  }
  return 0;
}
