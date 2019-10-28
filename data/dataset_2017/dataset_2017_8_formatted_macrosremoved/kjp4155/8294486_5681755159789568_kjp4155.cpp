#include <algorithm>
#include <assert.h>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <memory.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<int, int> Pi;
int tc;
vector<pair<double, double>> p;
void solve() {
  p.clear();
  double D;
  int N;
  scanf("%lf%d", &D, &N);
  double mx = 0;

  for (int i = 1; i <= N; i++) {
    double k, s;
    scanf("%lf%lf", &k, &s);
    p.push_back({D - k, s});
  }
  sort(p.begin(), p.end());
  for (auto e : p) {
    mx = max(e.first / e.second, mx);
  }

  printf("%.10lf\n", D / mx);
}

int main() {
  freopen("output.txt", "w", stdout);
  scanf("%d\n", &tc);
  for (int tt = 1; tt <= tc; tt++) {
    printf("Case #%d: ", tt);
    solve();
  }
}
