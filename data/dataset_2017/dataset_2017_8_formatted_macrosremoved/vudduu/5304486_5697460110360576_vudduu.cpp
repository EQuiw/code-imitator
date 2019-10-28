// vudduu - codejam 2017 round 1 A
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

vector<vector<pair<int, int>>> vInc;

void getMinMax(int inc, const vector<int> &w, int vi) {
  LL mini = ceil(double(inc) * 0.9);
  LL maxi = double(inc) * 1.1;
  vInc[vi].resize(w.size());
  for (int i = (0), _i = (w.size()); i < _i; ++i)
    vInc[vi][i] = make_pair(-1, -1);
  for (int i = (1), _i = (1000001); i < _i; ++i) {
    LL A = LL(mini) * LL(i);
    LL B = LL(maxi) * LL(i);
    if (A > 1200000LL)
      break;
    for (int j = (0), _j = (w.size()); j < _j; ++j) {
      if (A <= w[j] && LL(w[j]) <= B) {
        if (vInc[vi][j].first == -1)
          vInc[vi][j].first = i;
        vInc[vi][j].second = i;
      }
    }
  }
}

void solve() {
  int N, P;
  cin >> N >> P;
  vector<int> ing(N);
  vInc.resize(N);
  vector<vector<int>> v(N, vector<int>(P));
  for (int i = (0), _i = (N); i < _i; ++i)
    cin >> ing[i];
  for (int i = (0), _i = (N); i < _i; ++i) {
    for (int j = (0), _j = (P); j < _j; ++j)
      cin >> v[i][j];
    sort(v[i].begin(), v[i].end());
    getMinMax(ing[i], v[i], i);
  }
  int res = 0;
  sort(vInc[0].begin(), vInc[0].end());
  do {
    int c = 0;
    for (int i = (0), _i = (P); i < _i; ++i) {
      if (vInc[0][i].first == -1)
        continue;
      if (vInc[1][i].first == -1)
        continue;
      if (vInc[0][i].first <= vInc[1][i].first &&
          vInc[1][i].first <= vInc[0][i].second) {
        c++;
      } else if (vInc[1][i].first <= vInc[0][i].first &&
                 vInc[0][i].first <= vInc[1][i].second) {
        c++;
      }
    }
    res = max(res, c);
  } while (next_permutation(vInc[0].begin(), vInc[0].end()));
  cout << res << endl;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; cas++) {
    printf("Case #%d: ", cas);
    solve();
  }
}
