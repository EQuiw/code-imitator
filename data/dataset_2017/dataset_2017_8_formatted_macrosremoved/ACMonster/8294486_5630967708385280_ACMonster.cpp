// Problem A

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int get() {
  char c;
  while (c = getchar(), c != '-' && (c < '0' || c > '9'))
    ;
  bool flag = (c == '-');
  if (flag)
    c = getchar();
  int x = 0;
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return flag ? -x : x;
}

int main() {
  int totalTest = get();
  for (int test = 1; test <= totalTest; test++) {
    double l = get(), ans = 1e15;
    int n = get();
    for (int i = 0; i < n; i++) {
      double x = get(), v = get();
      ans = min(ans, l / ((l - x) / v));
    }
    printf("Case #%d: %0.10lf\n", test, ans);
  }
  return 0;
}
