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
  freopen("C-small-attempt0.in", "r", stdin);
  // freopen("input.txt" , "r" , stdin);
  freopen("C-small-attempt0.out", "w", stdout);
  int cas;
  scanf("%d", &cas);
  for (int ca = 1; ca <= cas; ca++) {
    printf("Case #%d: ", ca);
    int a, b, res = 0;
    scanf("%d %d", &a, &b);
    int p[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    for (int i = a; i <= b; i++) {
      int x = i, num = 0;
      while (x) {
        num++;
        x /= 10;
      }
      x = i;
      do {
        int k = x % 10;
        x /= 10;
        x = k * p[num - 1] + x;
        if (x > i && x <= b)
          res++;
      } while (x != i);
    }
    printf("%d\n", res);
  }
  return 0;
}