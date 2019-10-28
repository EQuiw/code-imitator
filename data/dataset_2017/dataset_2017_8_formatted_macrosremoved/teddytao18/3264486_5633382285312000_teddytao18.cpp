#include <iostream>
#include <map>
#include <math.h>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;

int numdig(long long n) {
  int res;
  for (res = 0; n; n /= 10)
    res++;
  return res;
}

long long dfs(long long n, int b, long long curr, int last) {
  if (!b)
    return curr;
  int z;
  curr *= 10;
  z = n / (long long)pow(10, b - 1);
  if (z < last)
    return 0;
  if (z == last)
    return dfs(n % (long long)pow(10, b - 1), b - 1, curr + z, z);
  return max((curr + z) * (long long)pow(10, b - 1) - 1,
             dfs(n % (long long)pow(10, b - 1), b - 1, curr + z, z));
}

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    int b;
    long long n, ans;
    scanf("%lld", &n);
    b = numdig(n);
    ans = dfs(n, b, 0, 0);
    printf("Case #%d: %lld\n", t, ans);
  }
}
