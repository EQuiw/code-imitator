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

#define FOR(i, a, b) for (int i = (a), _##i = (b); i < _##i; ++i)
#define F(i, a) FOR(i, 0, a)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair
#define S size()
typedef long long LL;

vector<vector<pair<int, int>>> vInc;

void getMinMax(int inc, const vector<int> &w, int vi) {
  LL mini = ceil(double(inc) * 0.9);
  LL maxi = double(inc) * 1.1;
  vInc[vi].resize(w.S);
  F(i, w.S) vInc[vi][i] = MP(-1, -1);
  FOR(i, 1, 1000001) {
    LL A = LL(mini) * LL(i);
    LL B = LL(maxi) * LL(i);
    if (A > 1200000LL)
      break;
    F(j, w.S) {
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
  F(i, N) cin >> ing[i];
  F(i, N) {
    F(j, P) cin >> v[i][j];
    sort(ALL(v[i]));
    getMinMax(ing[i], v[i], i);
  }
  int res = 0;
  sort(ALL(vInc[0]));
  do {
    int c = 0;
    F(i, P) {
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
  } while (next_permutation(ALL(vInc[0])));
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
