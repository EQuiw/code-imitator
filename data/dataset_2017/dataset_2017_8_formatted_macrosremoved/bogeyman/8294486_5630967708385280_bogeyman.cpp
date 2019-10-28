#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <regex>
#include <set>
#include <stack>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int S = int(1e3) + 10;
const double INF = 1e15 + 7;
const ll MOD = ll(1e9) + 7;
const double EPS = 1e-12;
const ll magic = ll(5e4);

int n;
int T;
double d;

int main() {
  freopen("/Users/user/Downloads/A-small-attempt0.in", "r", stdin);
  freopen("key.out", "w", stdout);
  cin >> T;
  for (int q = 1; q <= T; q++) {

    double v = INF;
    cin >> d >> n;
    for (int i = 0; i < n; i++) {
      double s, k;
      scanf("%lf%lf", &k, &s);
      v = min(v, d * s / (d - k));
    }
    printf("Case #%d: %lf\n", q, v);
  }
  return 0;
}
