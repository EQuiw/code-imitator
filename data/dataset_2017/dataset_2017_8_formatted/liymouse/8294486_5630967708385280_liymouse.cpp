#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef long long i64d;

using namespace std;

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int cas;
  scanf("%d", &cas);
  for (int ca = 1; ca <= cas; ca++) {
    printf("Case #%d: ", ca);
    int d, n;
    scanf("%d %d", &d, &n);
    double t = 0;
    for (int i = 0; i < n; i++) {
      int k, s;
      scanf("%d %d", &k, &s);
      t = max(t, (double)(d - k) / s);
    }
    printf("%lf\n", d / t);
  }
  return 0;
}