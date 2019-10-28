#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.0);

char ch[100][100];

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int T;
  cin >> T;

  for (int cas = 1; cas <= T; cas++) {

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
      cin >> ch[i] + 1;
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (ch[i][j] != '?') {
          for (int k = j - 1; k >= 1; k--) {
            if (ch[i][k] == '?') {
              ch[i][k] = ch[i][j];
            } else
              break;
          }
          for (int k = j + 1; k <= m; k++) {
            if (ch[i][k] == '?') {
              ch[i][k] = ch[i][j];
            } else
              break;
          }
        }
      }
    }

    for (int j = 1; j <= m; j++) {
      for (int i = 1; i <= n; i++) {
        if (ch[i][j] != '?') {
          for (int k = i - 1; k >= 1; k--) {
            if (ch[k][j] == '?') {
              ch[k][j] = ch[i][j];
            } else
              break;
          }
          for (int k = i + 1; k <= n; k++) {
            if (ch[k][j] == '?') {
              ch[k][j] = ch[i][j];
            } else
              break;
          }
        }
      }
    }

    cout << "Case #" << cas << ":" << endl;
    for (int i = 1; i <= n; i++) {
      cout << ch[i] + 1 << endl;
    }
  }
  return 0;
}
