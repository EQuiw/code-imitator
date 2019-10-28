// Problem B

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

long long get() {
  char c;
  while (c = getchar(), c != '-' && (c < '0' || c > '9'))
    ;
  bool flag = (c == '-');
  if (flag)
    c = getchar();
  long long x = 0;
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return flag ? -x : x;
}

int a[20];

int main() {
  int totalTest = get();
  for (int test = 1; test <= totalTest; test++) {
    long long n = get(), tmp = n;
    int m = 0;
    while (n) {
      a[m++] = n % 10;
      n /= 10;
    }
    printf("Case #%d: ", test);
    while (true) {
      int p = m - 1;
      while (p && a[p] <= a[p - 1])
        p--;
      if (!p)
        break;
      a[p]--;
      for (int i = 0; i < p; i++)
        a[i] = 9;
    }
    long long ans = 0;
    for (int i = m - 1; i >= 0; i--)
      ans = ans * 10 + a[i];
    cout << ans << endl;
  }
  return 0;
}
