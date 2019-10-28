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

int T, was[S];
string f[50];

int main() {
  freopen("/Users/user/Downloads/A-small-attempt1.in", "r", stdin);
  freopen("key.out", "w", stdout);
  cin >> T;
  for (int q = 1; q <= T; q++) {
    int n, m;
    memset(was, 0, S * sizeof(int));
    cin >> n >> m;
    for (int i = 0; i < n; i++)
      cin >> f[i];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) {
        if (f[i][j] != '?' && !was[f[i][j]]) {
          was[f[i][j]] = 1;
          int u = i, d = i;
          while (u > 0 && f[u - 1][j] == '?')
            u--;
          while (d < n - 1 && f[d + 1][j] == '?')
            d++;
          int l = j, r = j;
          while (l > 0) {
            bool flag = false;
            for (int k = u; k <= d; k++)
              if (f[k][l - 1] != '?')
                flag = true;
            if (flag)
              break;
            l--;
          }
          while (r < m - 1) {
            bool flag = false;
            for (int k = u; k <= d; k++)
              if (f[k][r + 1] != '?')
                flag = true;
            if (flag)
              break;
            r++;
          }
          for (int k = u; k <= d; k++)
            for (int jj = l; jj <= r; jj++)
              f[k][jj] = f[i][j];
        }
      }

    printf("Case #%d:\n", q);
    for (int i = 0; i < n; i++)
      cout << f[i] << "\n";
  }
  return 0;
}
