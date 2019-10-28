// vudduu - codejam 2017 round 1 B
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

double D, N;
vector<pair<int, int>> hs;

double getTime(double K, double V) { return (D - K) / V; }

void solve() {
  cin >> D >> N;
  hs.resize(N);
  for (int i = (0), _i = (N); i < _i; ++i)
    cin >> hs[i].first >> hs[i].second;
  sort(hs.rbegin(), hs.rend());
  double maxiK = hs[0].first;
  double maxiV = hs[0].second;
  double maxiT = getTime(hs[0].first, hs[0].second);
  for (int i = (0), _i = (N); i < _i; ++i) {
    double t = getTime(hs[i].first, hs[i].second);
    if (t > maxiT) {
      maxiT = t;
      maxiK = hs[i].first;
      maxiV = hs[i].second;
    } else {
      maxiK = hs[i].first;
      maxiV = (D - maxiK) / maxiT;
    }
  }
  maxiV = D / maxiT;
  printf("%.8lf\n", maxiV);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; cas++) {
    printf("Case #%d: ", cas);
    solve();
  }
}
