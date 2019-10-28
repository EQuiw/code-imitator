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

int solve() {
  int n, p;
  cin >> n >> p;
  vector<int> r;
  for (int i = 0; i < n; ++i) {
    int a;
    cin >> a;
    r.push_back(a);
  }
  vector<int> q[10];
  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < p; ++i) {
      int qi;
      cin >> qi;
      q[j].push_back(qi);
    }
  }
  int res = 0;
  if (n == 1) {
    for (int i = 0; i < p; ++i) {
      int a = ceil(q[0][i] / 1.1 / r[0]);
      int b = floor(q[0][i] / 0.9 / r[0]);
      if (a <= b) {
        res++;
      }
    }
    return res;
  }
  sort(q[1].begin(), q[1].end());
  do {
    int tmp = 0;
    for (int i = 0; i < p; ++i) {
      int a = ceil(q[0][i] / 1.1 / r[0]);
      int b = floor(q[0][i] / 0.9 / r[0]);
      int c = ceil(q[1][i] / 1.1 / r[1]);
      int d = floor(q[1][i] / 0.9 / r[1]);
      if (a <= b && c <= d && ((a <= c && b >= c) || (a >= c && a <= d))) {
        tmp++;
      }
      res = tmp > res ? tmp : res;
    }
  } while (next_permutation(q[1].begin(), q[1].end()));
  return res;
}

int main() {
  int t;
  cin >> t;
  for (int x = 1; x <= t; ++x) {
    cout << "Case #" << x << ": " << solve() << endl; // result
  }
  return 0;
}
