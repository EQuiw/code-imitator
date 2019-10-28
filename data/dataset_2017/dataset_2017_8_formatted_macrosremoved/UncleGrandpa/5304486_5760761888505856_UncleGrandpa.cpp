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
char c[35][35];
long long n, m;
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  long long T;
  cin >> T;
  long long ct = 0;
  while (T--) {
    ct++;
    cin >> n >> m;
    for (long long i = 1; i <= n; i++) {
      for (long long j = 1; j <= m; j++)
        cin >> c[i][j];
    }
    for (long long i = 1; i <= n; i++) {
      for (long long j = 1; j <= m; j++) {
        if (c[i][j] != '?') {
          for (long long k = i + 1; k <= n; k++) {
            if (c[k][j] != '?')
              break;
            c[k][j] = c[i][j];
          }
        }
      }
    }
    for (long long i = n; i >= 1; i--) {
      for (long long j = 1; j <= m; j++) {
        if (c[i][j] != '?') {
          for (long long k = i - 1; k >= 1; k--) {
            if (c[k][j] != '?')
              break;
            c[k][j] = c[i][j];
          }
        }
      }
    }
    for (long long i = 1; i <= n; i++) {
      for (long long j = 1; j <= m; j++) {
        if (c[i][j] != '?') {
          for (long long k = j + 1; k <= m; k++) {
            if (c[i][k] != '?')
              break;
            c[i][k] = c[i][j];
          }
        }
      }
    }
    for (long long i = 1; i <= n; i++) {
      for (long long j = m; j >= 1; j--) {
        if (c[i][j] != '?') {
          for (long long k = j - 1; k >= 1; k--) {
            if (c[i][k] != '?')
              break;
            c[i][k] = c[i][j];
          }
        }
      }
    }
    cout << "Case #" << ct << ":" << '\n';
    for (long long i = 1; i <= n; i++) {
      for (long long j = 1; j <= m; j++)
        cout << c[i][j];
      cout << '\n';
    }
  }
}
