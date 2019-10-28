//============================================================================
// Name        : A.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>

using namespace std;
int k[100050], s[100050];
int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int tt, ri = 0;
  scanf("%d", &tt);
  while (tt--) {
    int d, n;
    scanf("%d%d", &d, &n);
    double ans = -1;
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &k[i], &s[i]);
      double tmp = 1.0 * d * s[i] / (1.0 * d - k[i]);
      if (ans < 0 || tmp < ans)
        ans = tmp;
    }
    printf("Case #%d: %.8lf\n", ++ri, ans);
  }
  return 0;
}
