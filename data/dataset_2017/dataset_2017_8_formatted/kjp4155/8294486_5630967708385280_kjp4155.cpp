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

#define Fi first
#define Se second
#define pb(x) push_back(x)
#define sz(x) (int)x.size()
#define rep(i, n) for (int i = 0; i < n; i++)
#define repp(i, n) for (int i = 1; i <= n; i++)
#define all(x) x.begin(), x.end()

#define ABS(x) (((x) > 0) ? (x) : (-(x)))
#define MAX2(x, y) (((x) > (y)) ? (x) : (y))
#define MIN2(x, y) (((x) < (y)) ? (x) : (y))

#define MAX3(x, y, z)                                                          \
  ((x) > (y) ? ((x) > (z) ? (x) : (z)) : ((y) > (z) ? (y) : (z)))
#define MIN3(x, y, z)                                                          \
  ((x) < (y) ? ((x) < (z) ? (x) : (z)) : ((y) < (z) ? (y) : (z)))
#define MID3(val1, val2, val3)                                                 \
  MAX2(MIN2(MAX2(val1, val2), val3), MIN2(val1, val2))

#define geti(X) scanf("%d", &X)

#define INF 1987654321

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
  sort(all(p));
  for (auto e : p) {
    mx = max(e.Fi / e.Se, mx);
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