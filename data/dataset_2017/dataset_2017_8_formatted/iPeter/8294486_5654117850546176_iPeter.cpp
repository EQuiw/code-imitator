#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
//    0   1   2
int N, R, O, Y, G, B, V;
int s[2000];
int main(void) {
  int t;
  scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++) {
    scanf("%d%d%d%d%d%d%d", &N, &R, &O, &Y, &G, &B, &V);

    printf("Case #%d: ", tt);

    if (O > B || G > R || V > Y) {
      puts("IMPOSSIBLE");
      continue;
    }

    if (O == B && O > 0) {
      if (O + B < N) {
        puts("IMPOSSIBLE");
      } else {
        for (; O > 0; --O)
          printf("OB");
        puts("");
      }
      continue;
    }
    if (G == R && G > 0) {
      if (G + R < N) {
        puts("IMPOSSIBLE");
      } else {
        for (; G > 0; --G)
          printf("RG");
        puts("");
      }
      continue;
    }
    if (Y == V && V > 0) {
      if (Y + V < N) {
        puts("IMPOSSIBLE");
      } else {
        for (; V > 0; --V)
          printf("YV");
        puts("");
      }
      continue;
    }

    B -= O;
    R -= G;
    Y -= V;
    int m = B + R + Y;
    if (B > R + Y || R > B + Y || Y > B + R) {
      puts("IMPOSSIBLE");
      continue;
    }
    memset(s, -1, sizeof(s));

    int maxc = 0, c = R, c2 = Y, mc2 = 1, mc3 = 2;
    if (B > R && B > Y)
      maxc = 2, c = B, mc3 = 0;
    if (Y > B && Y > R)
      maxc = 1, c = Y, c2 = R, mc2 = 0;
    // printf("%d %d\n",c,c2);
    // printf("%d %d %d\n",maxc,mc2,mc3);

    for (int i = 0; i < c; i++) {
      s[i * 2] = maxc;
    }
    for (int i = m - 1 - (m % 2), j = 0; j < c2; i -= 2, ++j) {
      s[i] = mc2;
    }
    for (int i = 0; i < m; i++) {
      if (s[i] < 0)
        s[i] = mc3;
    }

    for (int i = 0; i < m; i++) {
      if (s[i] == 0) {
        printf("R");
        for (; G > 0; --G)
          printf("GR");
        // printf(G>0?"RGR":"R");
        // --G;
      } else if (s[i] == 1) {
        printf("Y");
        for (; V > 0; --V)
          printf("VY");
        // printf(V>0?"YVY":"Y");
        // --V;
      } else {
        printf("B");
        for (; O > 0; --O)
          printf("OB");
        // printf(O>0?"BOB":"B");
        // --O;
      }
    }
    puts("");
    // for(int i=0;i<m;++i)
    //   printf("%d",s[i]);
    // puts("");
  }
  return 0;
}
