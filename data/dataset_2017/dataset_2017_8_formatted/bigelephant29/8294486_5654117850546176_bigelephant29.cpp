#include <cstdio>
using namespace std;
int main() {
  int TN;
  scanf("%d", &TN);
  for (int casen = 1; casen <= TN; casen++) {
    printf("Case #%d: ", casen);
    int n, r, o, y, g, b, v;
    scanf("%d %d %d %d %d %d %d", &n, &r, &o, &y, &g, &b, &v);
    // r y b
    if (r > y && r > b) {
      // r is max
      if (r > y + b)
        printf("IMPOSSIBLE");
      else {
        char last = -1;
        for (int i = 0; i < r; i++) {
          putchar('R');
          if (y > b) {
            y--;
            putchar('Y');
            last = 'Y';
          } else {
            b--;
            putchar('B');
            last = 'B';
          }
        }
        while (y > 0 || b > 0) {
          if (last == 'Y') {
            putchar('B');
            b--;
            last = 'B';
          } else {
            putchar('Y');
            y--;
            last = 'Y';
          }
        }
      }
    } else if (y > b) {
      // y is max
      if (y > r + b)
        printf("IMPOSSIBLE");
      else {
        char last = -1;
        for (int i = 0; i < y; i++) {
          putchar('Y');
          if (r > b) {
            r--;
            putchar('R');
            last = 'R';
          } else {
            b--;
            putchar('B');
            last = 'B';
          }
        }
        while (r > 0 || b > 0) {
          if (last == 'R') {
            putchar('B');
            b--;
            last = 'B';
          } else {
            putchar('R');
            r--;
            last = 'R';
          }
        }
      }
    } else {
      // b is max
      if (b > r + y)
        printf("IMPOSSIBLE");
      else {
        char last = -1;
        for (int i = 0; i < b; i++) {
          putchar('B');
          if (y > r) {
            y--;
            putchar('Y');
            last = 'Y';
          } else {
            r--;
            putchar('R');
            last = 'R';
          }
        }
        while (y > 0 || r > 0) {
          if (last == 'R') {
            putchar('Y');
            y--;
            last = 'Y';
          } else {
            putchar('R');
            r--;
            last = 'R';
          }
        }
      }
    }
    puts("");
  }
  return 0;
}
