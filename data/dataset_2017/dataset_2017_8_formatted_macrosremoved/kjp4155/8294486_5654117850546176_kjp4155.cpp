#include <algorithm>
#include <assert.h>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <memory.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<int, int> Pi;
int N, M, T, K, tc;

void solve() {
  scanf("%d", &N);
  int R, O, Y, G, B, V;
  scanf("%d%d%d%d", &R, &O, &Y, &G);
  scanf("%d%d", &B, &V);
  if (R + B + Y == 1) {
    if (R == 1)
      printf("R");
    else if (B == 1)
      printf("B");
    else if (Y == 1)
      printf("Y");
    printf("\n");
    return;
  }
  if (R + B < Y || B + Y < R || Y + R < B) {
    printf("IMPOSSIBLE\n");
    return;
  }
  char a, b, c;
  a = 'R';
  b = 'B';
  c = 'Y';
  int ac = R, bc = B, cc = Y;
  if (ac < bc) {
    swap(ac, bc);
    swap(a, b);
  }
  if (ac < cc) {
    swap(ac, cc);
    swap(a, c);
  }
  if (bc < cc) {
    swap(bc, cc);
    swap(b, c);
  }

  char last = '1';
  while (ac > 0) {
    if (bc > cc) {
      printf("%c%c", a, b);
      bc--;
      ac--;
      last = b;
    } else {
      printf("%c%c", a, c);
      cc--;
      ac--;
      last = c;
    }
  }
  if (last == c) {
    while (bc > 0 && cc > 0) {
      printf("%c%c", b, c);
      bc--;
      cc--;
    }
  } else if (last == b) {
    while (cc > 0 && bc > 0) {
      printf("%c%c", c, b);
      cc--;
      bc--;
    }
  }
  if (bc > 0)
    printf("%c", b);
  if (cc > 0)
    printf("%c", c);

  printf("\n");
}

int main() {
  freopen("output.txt", "w", stdout);
  scanf("%d\n", &tc);
  for (int tt = 1; tt <= tc; tt++) {
    printf("Case #%d: ", tt);
    solve();
  }
}
