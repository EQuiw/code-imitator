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
  string s;
  cin >> s;
  int k;
  cin >> k;
  int l = -1, i = 0, n = s.length();
  char c = '-';
  int res = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '-') {
      res++;
      for (int j = i; j < i + k; ++j) {
        if (j >= n) {
          return -1;
        }
        s[j] = s[j] == '+' ? '-' : '+';
      }
    }
  }
  return res;
}

int main() {
  int t;
  cin >> t;
  for (int x = 1; x <= t; ++x) {
    int res = solve();
    cout << "Case #" << x << ": ";
    if (res >= 0) {
      cout << res;
    } else {
      cout << "IMPOSSIBLE";
    }
    cout << endl;
  }
  return 0;
}
