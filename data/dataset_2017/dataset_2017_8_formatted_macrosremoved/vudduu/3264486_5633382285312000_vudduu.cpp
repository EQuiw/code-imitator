// vudduu - codejam 2017 qualification round
// Problem B
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

string num;

void solve() {
  cin >> num;
  int it = -1;
  for (int i = (0), _i = (num.size() - 1); i < _i; ++i) {
    if (int(num[i]) > int(num[i + 1])) {
      it = i;
      while (it > 0 && num[it] == num[it - 1])
        it--;
      break;
    }
  }
  if (it != -1) {
    num[it]--;
    for (int i = (it + 1), _i = (num.size()); i < _i; ++i)
      num[i] = '9';
    if (num[it] == '0')
      num.erase(0, 1);
  }
  cout << num << endl;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; cas++) {
    printf("Case #%d: ", cas);
    solve();
  }
}
