#include <bits/stdc++.h>

using namespace std;

const int N = 55;

char a[N][N];
int n, m;

int main() {
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    int m, n;
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        cin >> a[i][j];
      }
    }
    for (int i = 1; i <= m; ++i) {
      for (int j = 2; j <= n; ++j) {
        if (a[i][j] == '?' && a[i][j - 1] != '?')
          a[i][j] = a[i][j - 1];
      }
      for (int j = n - 1; j >= 1; --j) {
        if (a[i][j] == '?' && a[i][j + 1] != '?')
          a[i][j] = a[i][j + 1];
      }
    }
    for (int j = 1; j <= n; ++j) {
      for (int i = 2; i <= m; ++i) {
        if (a[i][j] == '?' && a[i - 1][j] != '?')
          a[i][j] = a[i - 1][j];
      }
      for (int i = m - 1; i >= 1; --i) {
        if (a[i][j] == '?' && a[i + 1][j] != '?')
          a[i][j] = a[i + 1][j];
      }
    }

    cout << "Case #" << tc << ":" << endl;
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        cout << a[i][j];
      }
      cout << endl;
    }
  }
  return 0;
}