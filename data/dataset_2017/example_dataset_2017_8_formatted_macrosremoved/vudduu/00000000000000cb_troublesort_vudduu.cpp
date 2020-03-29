// vudduu - codejam 2018 QR
// Trouble Sort
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

int n;
int v[100001];

int main() {
  int T, aux;
  scanf("%d", &T);
  for (int cas = (0), _cas = (T); cas < _cas; ++cas) {
    scanf("%d", &n);
    vector<int> a, b;
    for (int i = (0), _i = (n); i < _i; ++i) {
      scanf("%d", &aux);
      if (i & 1)
        b.push_back(aux);
      else
        a.push_back(aux);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = (0), _i = (a.size()); i < _i; ++i)
      v[i * 2] = a[i];
    for (int i = (0), _i = (b.size()); i < _i; ++i)
      v[i * 2 + 1] = b[i];
    bool flag = true;
    for (int i = (1), _i = (n); i < _i; ++i) {
      if (v[i] < v[i - 1]) {
        printf("Case #%d: %d\n", cas + 1, i - 1);
        flag = false;
        break;
      }
    }
    if (flag) {
      printf("Case #%d: OK\n", cas + 1);
    }
  }
}
