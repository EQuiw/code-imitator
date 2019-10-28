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
  int T, t, d, n, i, j, x, y;
  double my, mx;
  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> d >> n;
    my = 0;
    mx = 1.0;
    for (i = 0; i < n; i++) {
      scanf("%d%d", &y, &x);
      y = d - y;
      if (my * x < mx * y) {
        my = y;
        mx = x;
      }
    }
    printf("Case #%d: %.6f\n", t, 1.0 * d / my * mx);
  }
  return 0;
}
