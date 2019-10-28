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
#define all(o) (o).begin(), (o).end()
#define mp(x, y) make_pair(x, y)
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define sz(x) ((int)(x).size())
#define x first
#define y second
#define pt pair<double, double>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int S = int(2e5) + 10;
const int INF = int(1e9) + 7;
const ll MOD = ll(1e4) + 7;
const double EPS = 1e-12;
const ll magic = ll(5e4);

int T;

int main() {
  freopen("/Users/user/Downloads/C-small-1-attempt0.in", "r", stdin);
  freopen("key.out", "w", stdout);
  cin >> T;
  for (int q = 1; q <= T; q++) {
    ll n, k;
    cin >> n >> k;
    ll l = n, r = n, k1 = k;
    while (k > 0) {
      if (k % 2 == 0)
        l /= 2;
      else
        l = (l - 1) / 2;
      k /= 2;
    }
    k = k1;
    while (k > 1) {
      if (k % 2 == 0)
        r /= 2;
      else
        r = (r - 1) / 2;
      k /= 2;
    }
    r /= 2;
    printf("Case #%d: %lld %lld\n", q, max(l, r), min(l, r));
  }
  return 0;
}
