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

#define FOR(i, a, b) for (int i = (a), _##i = (b); i < _##i; ++i)
#define F(i, a) FOR(i, 0, a)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair
#define S size()
typedef long long LL;

int n;
int v[100001];

int main() {
  int T, aux;
  scanf("%d", &T);
  F(cas, T) {
    scanf("%d", &n);
    vector<int> a, b;
    F(i, n) {
      scanf("%d", &aux);
      if (i & 1)
        b.PB(aux);
      else
        a.PB(aux);
    }
    sort(ALL(a));
    sort(ALL(b));
    F(i, a.S) v[i * 2] = a[i];
    F(i, b.S) v[i * 2 + 1] = b[i];
    bool flag = true;
    FOR(i, 1, n) {
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
