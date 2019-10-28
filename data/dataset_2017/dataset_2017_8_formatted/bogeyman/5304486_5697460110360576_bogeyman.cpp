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
//#define x first
//#define y second
#define pt pair<double, double>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int S = int(2e5) + 10;
const int INF = int(1e9) + 7;
const ll MOD = ll(1e4) + 7;
const double EPS = 1e-12;
const ll magic = ll(5e4);

int T, r[100], n, p, v[100][100];

int getmin(int a, int b) { return (10 * a + 11 * b - 1) / (11 * b); }

int getmax(int a, int b) { return (10 * a) / (9 * b); }

int main() {
  freopen("/Users/user/Downloads/B-small-attempt0.in", "r", stdin);
  freopen("key.out", "w", stdout);
  cin >> T;
  for (int q = 1; q <= T; q++) {
    cin >> n >> p;
    for (int i = 0; i < n; i++)
      scanf("%d", r + i);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < p; j++)
        scanf("%d", &v[i][j]);
    for (int i = 0; i < n; i++)
      sort(v[i], v[i] + p);
    vector<int> st(n, 0);
    int res = 0;
    bool flag = true;
    while (flag) {
      int pi = 0, minmax = getmax(v[0][st[0]], r[0]),
          maxmin = getmin(v[0][st[0]], r[0]);
      for (int i = 1; i < n; i++)
        if (getmax(v[i][st[i]], r[i]) < minmax) {
          pi = i;
          minmax = getmax(v[i][st[i]], r[i]);
        }
      for (int i = 1; i < n; i++)
        if (getmax(v[i][st[i]], r[i]) > maxmin)
          maxmin = getmin(v[i][st[i]], r[i]);
      if (minmax >= maxmin) {
        res++;
        for (int i = 0; i < n; i++)
          st[i]++;
      } else
        st[pi]++;
      for (int i = 0; i < n; i++)
        if (st[i] >= p)
          flag = false;
    }
    printf("Case #%d: %d\n", q, res);
  }
  return 0;
}
