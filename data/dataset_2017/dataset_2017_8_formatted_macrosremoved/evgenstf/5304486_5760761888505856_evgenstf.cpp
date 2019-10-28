#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

const int dd = 1e6;
const int inf = 1e9 + 7;

const double eps = 1e-8;

multiset<ll> dt;

int main() {
  //#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  //#endif

  int t;
  cin >> t;
  for (int tt = 0; tt < t; ++tt) {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n, vector<char>(m));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        cin >> a[i][j];
    for (int i = 0; i < n; ++i) {
      char pastc = '?';
      for (int j = 0; j < m; ++j) {
        if (a[i][j] == '?')
          a[i][j] = pastc;
        else
          pastc = a[i][j];
      }
      for (int j = m - 1; j >= 0; --j) {
        if (a[i][j] == '?')
          a[i][j] = pastc;
        else
          pastc = a[i][j];
      }
    }
    for (int j = 0; j < m; ++j) {
      char pastc = '?';
      for (int i = 0; i < n; ++i) {
        if (a[i][j] == '?')
          a[i][j] = pastc;
        else
          pastc = a[i][j];
      }
      for (int i = n - 1; i >= 0; --i) {
        if (a[i][j] == '?')
          a[i][j] = pastc;
        else
          pastc = a[i][j];
      }
    }
    cout << "Case #" << tt + 1 << ":\n";
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j)
        cout << a[i][j];
      cout << endl;
    }
  }

  return 0;
}
