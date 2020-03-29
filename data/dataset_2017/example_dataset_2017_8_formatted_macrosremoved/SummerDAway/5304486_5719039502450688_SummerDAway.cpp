#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

int ans, HD, AD, HK, AK, B, D;

void sim(int x, int y, int hd, int ad, int hk, int ak, int b, int d) {
  int ret = 0;
  while (true) {
    if (hk <= 0) {
      if (ans == -1) {
        ans = ret;
      } else {
        ans = min(ans, ret);
      }
      break;
    }
    if (x) {
      if (max(ak - d, 0) >= hd) {
        // cure;
        hd = HD;
      } else {
        x--;
        ak -= d;
        ak = max(ak, 0);
      }
    } else if (y) {
      if (ak >= hd) {
        // cure
        hd = HD;
      } else {
        y--;
        ad += b;
      }
    } else {
      if (ad >= hk) {
        // hit directly, don't cure
        hk -= ad;
      } else if (ak >= hd) {
        // cure
        hd = HD;
      } else {
        hk -= ad;
      }
    }

    hd -= ak;
    // printf("ret = %d %d %d\n", ret ,hd, hk);
    ret++;
    if (ret > 300)
      break;
  }
}

void work() {
  ans = -1;
  scanf("%d%d%d%d%d%d", &HD, &AD, &HK, &AK, &B, &D);
  for (int i = 0; i <= AK; ++i) {
    for (int j = 0; j <= HK; ++j) {
      sim(i, j, HD, AD, HK, AK, B, D);
    }
  }
  if (ans == -1)
    printf("IMPOSSIBLE\n");
  else
    printf("%d\n", ans);
}

int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-small-attempt0.out", "w", stdout);
  int TC;
  scanf("%d", &TC);
  for (int tc = 1; tc <= TC; ++tc) {
    printf("Case #%d: ", tc);
    work();
  }
}
