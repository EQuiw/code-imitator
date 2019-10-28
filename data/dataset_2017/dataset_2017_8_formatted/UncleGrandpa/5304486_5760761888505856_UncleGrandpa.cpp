/*input
3
3 3
G??
?C?
??J
3 4
CODE
????
?JAM
2 2
CA
KE
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
#define sp ' '
#define endl '\n'
#define fi first
#define se second
#define mp make_pair
#define int long long
#define N 35

char c[N][N];
int n, m;
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
#ifdef UncleGrandpa
  freopen("1test.inp", "r", stdin);
  freopen("1test.out", "w", stdout);
#endif
  int T;
  cin >> T;
  int ct = 0;
  while (T--) {
    ct++;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++)
        cin >> c[i][j];
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (c[i][j] != '?') {
          for (int k = i + 1; k <= n; k++) {
            if (c[k][j] != '?')
              break;
            c[k][j] = c[i][j];
          }
        }
      }
    }
    for (int i = n; i >= 1; i--) {
      for (int j = 1; j <= m; j++) {
        if (c[i][j] != '?') {
          for (int k = i - 1; k >= 1; k--) {
            if (c[k][j] != '?')
              break;
            c[k][j] = c[i][j];
          }
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (c[i][j] != '?') {
          for (int k = j + 1; k <= m; k++) {
            if (c[i][k] != '?')
              break;
            c[i][k] = c[i][j];
          }
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = m; j >= 1; j--) {
        if (c[i][j] != '?') {
          for (int k = j - 1; k >= 1; k--) {
            if (c[i][k] != '?')
              break;
            c[i][k] = c[i][j];
          }
        }
      }
    }
    cout << "Case #" << ct << ":" << endl;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++)
        cout << c[i][j];
      cout << endl;
    }
  }
}