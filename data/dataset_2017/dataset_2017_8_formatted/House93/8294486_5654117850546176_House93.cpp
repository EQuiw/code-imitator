#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 1010

int T, t = 1;

int n, R, O, Y, G, B, V;
char ans[N];
int d[10];
char f[10];

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d%d%d%d", &n, &R, &O, &Y, &G, &B, &V);
    if (R >= Y && R >= B) {
      d[0] = R;
      f[0] = 'R';
      if (Y >= B) {
        d[1] = Y;
        f[1] = 'Y';
        d[2] = B;
        f[2] = 'B';
      } else {
        d[2] = Y;
        f[2] = 'Y';
        d[1] = B;
        f[1] = 'B';
      }
    } else if (Y >= R && Y >= B) {
      d[0] = Y;
      f[0] = 'Y';
      if (R >= B) {
        d[1] = R;
        f[1] = 'R';
        d[2] = B;
        f[2] = 'B';
      } else {
        d[2] = R;
        f[2] = 'R';
        d[1] = B;
        f[1] = 'B';
      }
    } else {
      d[0] = B;
      f[0] = 'B';
      if (R >= Y) {
        d[1] = R;
        f[1] = 'R';
        d[2] = Y;
        f[2] = 'Y';
      } else {
        d[2] = R;
        f[2] = 'R';
        d[1] = Y;
        f[1] = 'Y';
      }
    }
    int idx = 0;
    int m = d[0] - d[1];
    for (int i = 0; i < d[2]; ++i) {
      ans[idx++] = f[0];
      ans[idx++] = f[1];
      if (m) {
        --m;
        ans[idx++] = f[0];
      }
      ans[idx++] = f[2];
    }
    for (int i = 0; i < d[1] - d[2]; ++i) {
      ans[idx++] = f[0];
      ans[idx++] = f[1];
    }
    if (idx != n) {
      printf("Case #%d: IMPOSSIBLE\n", t++);
    } else {
      ans[idx] = '\0';
      printf("Case #%d: %s\n", t++, ans);
    }
  }
  return 0;
}
