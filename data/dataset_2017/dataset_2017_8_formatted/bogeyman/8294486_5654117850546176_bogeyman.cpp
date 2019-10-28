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
#define xx first
#define yy second
#define pt pair<double, double>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int S = int(1e3) + 10;
const double INF = 1e15 + 7;
const ll MOD = ll(1e9) + 7;
const double EPS = 1e-12;
const ll magic = ll(5e4);

int n, T, aa[6];

int main() {
  freopen("/Users/user/Downloads/B-small-attempt3.in", "r", stdin);
  freopen("key.out", "w", stdout);
  cin >> T;
  for (int q = 1; q <= T; q++) {
    cin >> n;
    for (int i = 0; i < 6; i++)
      cin >> aa[i];
    pair<int, char> v[3] = {{aa[0], 'R'}, {aa[2], 'Y'}, {aa[4], 'B'}};
    sort(v, v + 3);
    int r = v[2].xx, y = v[1].xx, b = v[0].xx;
    char r0 = v[2].yy, y0 = v[1].yy, b0 = v[0].yy;
    if (!(r >= y && y >= b))
      exit(1);

    if (b + y < r)
      printf("Case #%d: IMPOSSIBLE\n", q);
    else {
      bool flag = false;
      if ((r + y + b) % 2 == 1) {
        flag = true;
        r--;
      }
      int an = (r + y - b) / 2;
      int bn = (r + b - y) / 2;
      int cn = (b + y - r) / 2;
      printf("Case #%d: ", q);
      for (int i = 0; i < an; i++) {
        printf("%c", r0);
        printf("%c", y0);
      }
      for (int i = 0; i < bn; i++) {
        printf("%c", r0);
        printf("%c", b0);
      }
      if (flag)
        printf("%c", r0);
      for (int i = 0; i < cn; i++) {
        printf("%c", y0);
        printf("%c", b0);
      }
      printf("\n");
    }
  }
  return 0;
}
