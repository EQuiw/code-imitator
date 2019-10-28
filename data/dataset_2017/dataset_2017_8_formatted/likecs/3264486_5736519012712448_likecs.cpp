/******************************************
 *    AUTHOR:         BHUVNESH JAIN        *
 *    INSTITUITION:   BITS PILANI, PILANI  *
 ******************************************/
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

int main() {
  ios_base::sync_with_stdio(false);
  int t, n, k, x, y, l;
  cin >> t;
  for (int T = 1; T <= t; ++T) {
    cout << "Case #" << T << ": ";

    string s, a;
    cin >> s >> k;
    n = s.length();
    l = 1 << n;
    x = INT_MAX;
    for (int i = 0; i < l; ++i) {
      a = s;
      vector<int> b;
      for (int j = 0; j < n; ++j) {
        if (i & (1 << j)) {
          b.push_back(j);
        }
      }
      y = 0;
      for (int j : b) {
        if (j + k <= n) {
          for (int u = j; u <= j + k - 1; ++u) {
            if (a[u] == '-') {
              a[u] = '+';
            } else {
              a[u] = '-';
            }
          }
          y += 1;
        } else {
          y = INT_MAX;
          break;
        }
      }
      for (int j = 0; j < n; ++j) {
        if (a[j] == '-') {
          y = INT_MAX;
          break;
        }
      }
      x = min(x, y);
    }
    if (x == INT_MAX) {
      cout << "IMPOSSIBLE\n";
    } else {
      cout << x << "\n";
    }
  }
  return 0;
}