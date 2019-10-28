#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef long double LD;

#define dprintf(...) fprintf(stderr, __VA_ARGS__)

int cond = 1;
#define DB(X)                                                                  \
  {                                                                            \
    if (cond) {                                                                \
      cerr << "Line:" << __LINE__ << ", " << #X << " = " << X << endl;         \
    }                                                                          \
  }

LL getSize(int p, LL d, LL n) {
  if (p == 0) {
    return n;
  }
  LL x = getSize(p - 1, d >> 1, n);
  return (x - (d % 2)) / 2;
}

void solve() {
  LL n, k;
  cin >> n >> k;
  int p = 0;
  LL x = 1;
  if (k == 1) {
    cout << n / 2 << " " << (n - 1) / 2;
    return;
  }
  while (x * 2 <= k) {
    x *= 2;
    p++;
  }
  x--;
  LL diff = k - x;
  LL w = getSize(p, diff - 1, n);
  cout << w / 2 << " " << (w - 1) / 2;
}

void solve2() {
  LL n, k;
  cin >> n >> k;
  vector<int> dn(1000005, 0);
  dn[n] = 1;
  LL i = n + 1;
  while (k-- > 1) {
    while (dn[i] == 0) {
      --i;
    };
    dn[i]--;
    dn[i / 2]++;
    dn[(i - 1) / 2]++;
  }
  while (dn[i] == 0) {
    --i;
  }
  cout << i / 2 << " " << (i - 1) / 2;
}

int main() {
  int t;
  cin >> t;
  for (int x = 1; x <= t; ++x) {
    cout << "Case #" << x << ": ";
    solve2();
    cout << endl; // result
  }
  return 0;
}
