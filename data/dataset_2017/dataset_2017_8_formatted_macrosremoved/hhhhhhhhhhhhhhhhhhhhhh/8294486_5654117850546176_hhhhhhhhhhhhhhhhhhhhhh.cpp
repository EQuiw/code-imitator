#include <bits/stdc++.h>
using namespace std;

int sz[7], ret[1010];
const int flag[7] = {1, (1 | 2), 2, (2 | 4), 4, (1 | 4)};
const char name[7] = {'R', 'O', 'Y', 'G', 'B', 'V'};

int main() {
  freopen("B-small-attempt1.in", "r", stdin);
  freopen("B-small-attempt1.out", "w", stdout);

  int test;
  scanf("%d", &test);
  for (int _ = 1; _ <= test; _++) {
    int n;
    scanf("%d", &n);
    int mx = 0;
    for (int i = 0; i < 6; i++) {
      scanf("%d", &sz[i]);
      mx = max(mx, sz[i]);
    }

    printf("Case #%d: ", _);
    if (mx * 2 > n) {
      puts("IMPOSSIBLE");
    } else {
      int totret = 0;
      while (n--) {
        int mx = 0, id = -1;
        int bk = totret ? ret[totret - 1] : -1;
        int x = totret ? ret[0] : 0;
        for (int i = x, j = 0; j < 3; (i += 2) %= 6, j++) {
          if (i == bk)
            continue;
          if (sz[i] > mx) {
            id = i;
            mx = sz[i];
          }
        }
        sz[id]--;
        ret[totret++] = id;
      }
      if (ret[0] == ret[totret - 1]) {
        puts("");
      }
      for (int i = 0; i < totret; i++) {
        putchar(name[ret[i]]);
      }
      puts("");
    }
  }
  return 0;
}
