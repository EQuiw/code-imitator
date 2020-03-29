// vudduu - codejam 2018 QR
// Saving The Universe Again
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

string p;
int n;
LL d;

bool getValid() {
  LL dam = 1, t = 0;
  for (int i = (0), _i = (n); i < _i; ++i) {
    if (p[i] == 'S')
      t += dam;
    else
      dam *= 2LL;
    if (t > d)
      return false;
  }
  return true;
}

void makeChange() {
  int it = n - 1;
  while (it && (p[it - 1] == 'S' || p[it] == 'C'))
    it--;
  p[it - 1] = 'S';
  p[it] = 'C';
}

int main() {
  int T;
  cin >> T;
  for (int cas = (0), _cas = (T); cas < _cas; ++cas) {
    printf("Case #%d: ", cas + 1);
    cin >> d >> p;
    n = p.size();
    int cs = 0;
    for (int i = (0), _i = (n); i < _i; ++i) {
      if (p[i] == 'S')
        cs++;
    }
    if (cs > d) {
      printf("IMPOSSIBLE\n");
    } else {
      int c = 0;
      while (!getValid()) {
        makeChange();
        c++;
      }
      printf("%d\n", c);
    }
  }
}
