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

void test(string s) {
  int n = s.length();
  for (int i = 0; i < n; ++i) {
    if (s[i] == s[i + 1 % n]) {
      cout << "WRONG!";
      return;
    }
  }
}

string solve() {
  int n;
  cin >> n;
  int r, o, y, g, b, v;
  cin >> r >> o >> y >> g >> b >> v;

  vector<char> m = {'R', 'Y', 'B'};
  vector<int> x = {r, y, b};
  for (int i = 0; i < 3; ++i) {
    char tmp = m[i];
    int t = x[i];
    int j = i + 1;
    while (j < 3 && x[j] < x[i]) {
      x[j - 1] = x[j];
      m[j - 1] = m[j];
      j++;
    }
    m[j - 1] = tmp;
    x[j - 1] = t;
  }

  ostringstream is("");
  int a1 = x[0] + x[1] - x[2];
  int a2 = x[2] - x[1];
  int a3 = x[2] - x[0];
  if (a1 < 0 || a2 < 0 || a3 < 0) {
    return "IMPOSSIBLE";
  }

  while (a1-- > 0) {
    is << m[0] << m[2] << m[1];
  }
  while (a2-- > 0) {
    is << m[2] << m[0];
  }
  while (a3-- > 0) {
    is << m[2] << m[1];
  }

  test(is.str());
  return is.str();
}

int main() {
  int t;
  cin >> t;
  for (int x = 1; x <= t; ++x) {
    cout << "Case #" << x << ": " << solve() << endl; // result
  }
  return 0;
}
