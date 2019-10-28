//============================================================================
// Name        : jam17cpp.cpp
// Author      : Javier Sardinas
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

void p1small() {

  int t, k;
  char s[1000];
  scanf("%d", &t);
  int c = 0;
  while (t--) {
    ++c;
    scanf("%s%d", s, &k);
    int n = strlen(s);
    if (k > n) {
      printf("Case #%d: IMPOSSIBLE\n", c);
      continue;
    }
    int i;
    int count = 0;
    for (i = 0; i <= n - k; ++i)
      if (s[i] == '-') {
        count++;
        for (int j = 0; j < k; ++j)
          s[i + j] = '-' + '+' - s[i + j];
      }
    bool b = 1;
    for (; i < n && b; ++i)
      if (s[i] == '-') {
        printf("Case #%d: IMPOSSIBLE\n", c);
        b = 0;
      }
    if (b)
      printf("Case #%d: %d\n", c, count);
  }
}

int main() {

  p1small();
  return 0;
}
