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

#define FOR(i, a, b) for (int i = (a), _##i = (b); i < _##i; ++i)
#define F(i, a) FOR(i, 0, a)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair
#define S size()
typedef long long LL;

int N;
int R, O, Y, G, B, V;

void solve() {
  cin >> N >> R >> O >> Y >> G >> B >> V;
  vector<pair<int, char>> v;
  v.PB(MP(R, 'R'));
  v.PB(MP(Y, 'Y'));
  v.PB(MP(B, 'B'));
  sort(ALL(v));
  string solu(N, 'X');
  if (v[2].first <= v[0].first + v[1].first) {
    int it = 0;
    F(i, 3) {
      F(j, v[i].first) {
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
