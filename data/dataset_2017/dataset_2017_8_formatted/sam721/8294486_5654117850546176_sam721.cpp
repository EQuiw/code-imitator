#include <bits/stdc++.h>
#define LL long long
#define VI vector<int>
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define INF 0x3f3f3f3f
using namespace std;
char A[1000010];
char S[3];
int C[3];
int main() {
  int t, n, r, o, y, g, b, v;
  scanf("%d", &t);
  for (int c = 1; c <= t; c++) {
    scanf("%d %d %d %d %d %d %d", &n, &r, &o, &y, &g, &b, &v);
    printf("Case #%d: ", c);
    if (2 * g > r || 2 * o > b || 2 * v > y)
      printf("IMPOSSIBLE\n");
    else {
      r -= g;
      b -= o;
      y -= v;
      int N = r + b + y;
      char col;
      for (int i = 0; i < N; i++)
        A[i] = '*';
      A[N] = '\0';
      if (r > b && r > y)
        col = 'R';
      else if (b > r && b > y)
        col = 'B';
      else
        col = 'Y';
      for (int i = 0; i < N; i += 2) {
        A[i] = col;
        if (col == 'R')
          r--;
        else if (col == 'B')
          b--;
        else
          y--;
        if (col == 'R' && !r)
          break;
        if (col == 'Y' && !y)
          break;
        if (col == 'B' && !b)
          break;
      }
      if (A[0] == A[N - 1] || (col == 'R' && r) || (col == 'Y' && y) ||
          (col == 'B' && b)) {
        printf("IMPOSSIBLE\n");
        continue;
      }
      if (col == 'R') {
        S[0] = 'B';
        S[1] = 'Y';
        C[0] = b;
        C[1] = y;
      } else if (col == 'Y') {
        S[0] = 'R';
        S[1] = 'B';
        C[0] = r;
        C[1] = b;
      } else {
        S[0] = 'R';
        S[1] = 'Y';
        C[0] = r;
        C[1] = y;
      }
      int s = 0;
      for (int i = N - 1; i >= 0; i--) {
        if (A[i] == '*') {
          if (s == 0 && C[0]) {
            A[i] = S[0];
            s = 1 - s;
            C[0]--;
          } else if (s == 1 && C[1]) {
            A[i] = S[1];
            s = 1 - s;
            C[1]--;
          } else if (C[0] == 0 && C[1] == 0)
            break;
          else if (C[0]) {
            A[i] = S[0];
            C[0]--;
          } else if (C[1]) {
            A[i] = S[1];
            C[1]--;
          }
        }
      }
      bool ok = true;
      for (int i = 0; i < N && ok; i++) {
        if (A[i] == '*' || (A[i] == A[(i + 1) % N]))
          ok = false;
      }
      if (!ok)
        printf("IMPOSSIBLE\n");
      else {
        for (int i = 0; i < N; i++) {
          if (A[i] == 'R') {
            if (g) {
              printf("RGR");
              g--;
            } else
              printf("R");
          } else if (A[i] == 'B') {
            if (o) {
              printf("BOB");
              o--;
            } else
              printf("B");
          } else if (A[i] == 'Y') {
            if (v) {
              printf("YVY");
              v--;
            } else
              printf("Y");
          }
        }
        printf("\n");
      }
    }
  }
  return 0;
}