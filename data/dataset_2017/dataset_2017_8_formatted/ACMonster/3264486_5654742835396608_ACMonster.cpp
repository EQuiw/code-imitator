// Problem C

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
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

map<long long, long long> ans;

long long cnt(long long n, long long m) {
  if (n < m)
    return 0;
  if (ans[n] != 0)
    return ans[n];
  long long a = (n + 1) / 2 - 1;
  long long b = n / 2;
  return ans[n] = cnt(a, m) + cnt(b, m) + 1;
}

int main() {
  int totalTest = get();
  for (int test = 1; test <= totalTest; test++) {
    long long n = get(), k = get();

    long long l = 0, r = n;
    while (l < r) {
      long long mid = (l + r + 1) / 2;
      ans.clear();
      if (cnt(n, mid) < k)
        r = mid - 1;
      else
        l = mid;
    }

    printf("Case #%d: ", test);
    cout << (l / 2) << ' ' << ((l + 1) / 2 - 1) << endl;
  }
  return 0;
}
