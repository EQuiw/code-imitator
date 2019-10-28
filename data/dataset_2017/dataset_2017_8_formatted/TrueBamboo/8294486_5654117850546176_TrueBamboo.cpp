#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

#include <fstream>
FILE *fin = freopen("a.in", "r", stdin);
FILE *fout = freopen("a.out", "w", stdout);

int main() {
  int T, t, n, r, o, y, g, b, v, first, i, j, p;
  double my, mx;
  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> n >> r >> o >> y >> g >> b >> v;
    printf("Case #%d: ", t);
    if (r + y < b || r + b < y || b + y < r) {
      printf("IMPOSSIBLE");
    } else {
      first = 0;
      for (i = 0; i < n; i++) {
        if (first == 0) {
          if (r >= y && r >= b) {
            first = 1;
          } else if (y >= r && y >= b) {
            first = 2;
          } else
            first = 3;
          j = first;
        } else {
          if (p == 1) {
            if (y > b) {
              j = 2;
            } else if (y < b) {
              j = 3;
            } else if (first == 2) {
              j = 2;
            } else
              j = 3;
          } else if (p == 2) {
            if (r > b) {
              j = 1;
            } else if (r < b) {
              j = 3;
            } else if (first == 1) {
              j = 1;
            } else
              j = 3;
          } else {
            if (r > y) {
              j = 1;
            } else if (r < y) {
              j = 2;
            } else if (first == 1) {
              j = 1;
            } else
              j = 2;
          }
        }
        if (j == 1) {
          r--;
          printf("R");
        } else if (j == 2) {
          y--;
          printf("Y");
        } else {
          b--;
          printf("B");
        }
        p = j;
      }
    }
    printf("\n");
  }
  return 0;
}
