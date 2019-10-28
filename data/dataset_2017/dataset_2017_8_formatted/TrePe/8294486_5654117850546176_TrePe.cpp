#include <algorithm>
#include <stdio.h>
#include <string.h>

int N, R, O, Y, G, B, V, m1, m2, m3;
int i;
char a[1001], c1, c2, c3;

int main() {
  int cases;
  scanf("%d", &cases);
  for (int kejs = 1; kejs <= cases; kejs++) {
    printf("Case #%d: ", kejs);
    scanf("%d%d%d%d%d%d%d", &N, &R, &O, &Y, &G, &B, &V);
    if (R >= Y && R >= B) {
      c1 = 'R';
      m1 = R;
      if (Y >= B) {
        c2 = 'Y';
        m2 = Y;
        c3 = 'B';
        m3 = B;
      } else {
        c2 = 'B';
        m2 = B;
        c3 = 'Y';
        m3 = Y;
      }
    } else if (Y >= R && Y >= B) {
      c1 = 'Y';
      m1 = Y;
      if (R >= B) {
        c2 = 'R';
        m2 = R;
        c3 = 'B';
        m3 = B;
      } else {
        c2 = 'B';
        m2 = B;
        c3 = 'R';
        m3 = R;
      }
    } else {
      c1 = 'B';
      m1 = B;
      if (R >= Y) {
        c2 = 'R';
        m2 = R;
        c3 = 'Y';
        m3 = Y;
      } else {
        c2 = 'Y';
        m2 = Y;
        c3 = 'R';
        m3 = R;
      }
    }
    if (m3 == 0) {
      if (m1 != m2)
        printf("IMPOSSIBLE\n");
      else {
        for (i = 0; i < N; i++) {
          a[i] = i % 2 ? c1 : c2;
        }
        a[N] = '\0';
        printf("%s\n", a);
      }
    } else {
      a[N] = '\0';
      a[0] = c3;
      m3--;
      for (i = 1; i < N; i++) {
        if (m1 > 0 && a[i - 1] != c1) {
          a[i] = c1;
          m1--;
        } else if (m2 > 0 && a[i - 1] != c2) {
          a[i] = c2;
          m2--;
        } else if (m3 > 0 && a[i - 1] != c3) {
          a[i] = c3;
          m3--;
        } else
          break;
        if (m2 > m1) {
          std::swap(m1, m2);
          std::swap(c1, c2);
        }
        if (m3 > m2) {
          std::swap(m3, m2);
          std::swap(c3, c2);
        }
      }
      if (i < N)
        printf("IMPOSSIBLE\n");
      else if (a[0] != a[N - 1])
        printf("%s\n", a);
      else {
        std::swap(a[0], a[1]);
        if (a[1] == a[2])
          std::swap(a[1], a[2]);
        printf("%s\n", a);
      }
    }
  }
  return 0;
}
