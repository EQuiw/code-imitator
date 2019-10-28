// vudduu - codejam 2017 round 1 A
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

int N, M;
vector<string> vs;

void solve() {
  cin >> N >> M;
  vs.resize(N);
  for (int i = (0), _i = (N); i < _i; ++i) {
    cin >> vs[i];
    char ch = '.';
    for (int j = (0), _j = (M); j < _j; ++j) {
      if (vs[i][j] != '?') {
        if (ch == '.') {
          for (int k = (0), _k = (j); k < _k; ++k)
            vs[i][k] = vs[i][j];
        }
        ch = vs[i][j];
      } else {
        if (ch != '.')
          vs[i][j] = ch;
      }
    }
  }
  if (vs[0][0] == '?') {
    for (int k = (0), _k = (N); k < _k; ++k) {
      if (vs[k][0] != '?') {
        for (int i = k - 1; i >= 0; i--) {
          for (int j = (0), _j = (M); j < _j; ++j) {
            vs[i][j] = vs[i + 1][j];
          }
        }
        break;
      }
    }
  }
  for (int i = (1), _i = (N); i < _i; ++i) {
    if (vs[i][0] == '?') {
      for (int j = (0), _j = (M); j < _j; ++j) {
        vs[i][j] = vs[i - 1][j];
      }
    }
  }
  for (int i = (0), _i = (N); i < _i; ++i) {
    cout << vs[i] << endl;
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; cas++) {
    printf("Case #%d:\n", cas);
    solve();
  }
}
