// vudduu - codejam 2017 round 1 B
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

int N;
int R, O, Y, G, B, V;

void solve() {
  cin >> N >> R >> O >> Y >> G >> B >> V;
  vector<pair<int, char>> v;
  v.push_back(make_pair(R, 'R'));
  v.push_back(make_pair(Y, 'Y'));
  v.push_back(make_pair(B, 'B'));
  sort(v.begin(), v.end());
  string solu(N, 'X');
  if (v[2].first <= v[0].first + v[1].first) {
    int it = 0;
    for (int i = (0), _i = (3); i < _i; ++i) {
      for (int j = (0), _j = (v[i].first); j < _j; ++j) {
        solu[it] = v[i].second;
        it += 2;
        if (it >= N)
          it = 1;
      }
    }
  } else {
    solu = "IMPOSSIBLE";
  }
  cout << solu << endl;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; cas++) {
    printf("Case #%d: ", cas);
    solve();
  }
}
