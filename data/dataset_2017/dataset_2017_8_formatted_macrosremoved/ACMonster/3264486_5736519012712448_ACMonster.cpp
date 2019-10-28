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
    string s;
    cin >> s;
    int n = s.size(), k = get(), ans = 0;
    for (int i = 0; i + k <= n; i++) {
      if (s[i] == '+')
        continue;
      for (int j = i; j < i + k; j++)
        s[j] = (s[j] == '+') ? '-' : '+';
      ans++;
    }
    bool flag = true;
    for (int i = 0; flag && i < n; i++)
      flag = (s[i] == '+');
    printf("Case #%d: ", test);
    if (flag)
      printf("%d\n", ans);
    else
      printf("IMPOSSIBLE\n");
  }
  return 0;
}
