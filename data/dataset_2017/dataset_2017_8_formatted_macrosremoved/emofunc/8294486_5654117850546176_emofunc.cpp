#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
int T_T;
int n;
int R, O, Y, G, B, V;
int str[10000];
int main(void) {

  scanf("%d", &T_T);
  for (int cas = 1; cas <= T_T; cas++) {
    scanf("%d%d%d%d%d%d%d", &n, &R, &O, &Y, &G, &B, &V);
    printf("n = %d R = %d O = %d Y = %d G = %d B = %d V = %d\n", n, R, O, Y, G,
           B, V);
    printf("Case #%d: ", cas);
    if ((G && R <= G) || (V && Y <= V) || (B && B <= O)) {
      printf("IMPOSSIBLE\n");
      continue;
    }

    int nR = R - G, nY = Y - V, nB = B - O;
    printf("nR = %d, nY = %d, nB = %d\n", nR, nY, nB);
    int i = 0, nn = nR + nY + nB;
    int mx = max(nR, max(nY, nB));
    if (nR == mx)
      str[i++] = 'R', nR--;
    else if (nY == mx)
      str[i++] = 'Y', nY--;
    else if (nB == mx)
      str[i++] = 'B', nB--;
    while (nR || nY || nB) {
      if (str[i - 1] == 'R') {
        if (nY > nB)
          str[i++] = 'Y', nY--;
        else if (nB > nY)
          str[i++] = 'B', nB--;
        else {
          if (nY == 0 && nB == 0)
            break;
          if (str[0] == 'B')
            str[i++] = 'Y', nY--;
          else
            str[i++] = 'B', nB--;
        }
      } else if (str[i - 1] == 'Y') {
        if (nR > nB)
          str[i++] = 'R', nR--;
        else if (nB > nR)
          str[i++] = 'B', nB--;
        else {
          if (nR == 0 && nB == 0)
            break;
          if (str[0] == 'B')
            str[i++] = 'R', nR--;
          else
            str[i++] = 'B', nB--;
        }
      } else if (str[i - 1] == 'B') {
        if (nY > nR)
          str[i++] = 'Y', nY--;
        else if (nR > nY)
          str[i++] = 'R', nR--;
        else {
          if (nY == 0 && nR == 0)
            break;
          if (str[0] == 'Y')
            str[i++] = 'R', nR--;
          else
            str[i++] = 'Y', nY--;
        }
      }
    }
    for (int i = 0; i < nn; i++)
      printf("%c", str[i]);
    puts("");
    if (nR || nY || nB || str[0] == str[n - 1]) {
      printf("IMPOSSIBLE\n");
      continue;
    }
    printf("??\n");
    int fR = 1, fY = 1, fB = 1;
    for (int i = 0; i < nn; i++) {
      if (fR && str[i] == 'R') {
        printf("R");
        for (int j = 0; j < G; j++)
          printf("GR");
        fR = 0;
      } else if (fY && str[i] == 'Y') {
        printf("Y");
        for (int j = 0; j < V; j++)
          printf("VY");
        fY = 0;
      } else if (fB && str[i] == 'B') {
        printf("B");
        for (int j = 0; j < O; j++)
          printf("OB");
      } else
        printf("%c", str[i]);
    }
    puts("");
  }
  return 0;
}
