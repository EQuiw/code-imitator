// vudduu - codejam 2017 qualification round
// Problem A
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <utility>
#include <vector>
using namespace std;

typedef long long LL;

string str;
int k;

void solve() {
  cin >> str >> k;
  int n = str.size();
  int res = 0;
  for (int i = 0; i <= n - k; i++) {
    if (str[i] != '+') {
      for (int j = (0), _j = (k); j < _j; ++j)
        str[i + j] = (str[i + j] == '+') ? '-' : '+';
      res++;
    }
  }
  bool flag = true;
  for (int i = (0), _i = (n); i < _i; ++i) {
    if (str[i] != '+')
      flag = false;
  }
  if (flag)
    printf("%d\n", res);
  else
    printf("IMPOSSIBLE\n");
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; cas++) {
    printf("Case #%d: ", cas);
    solve();
  }
}
