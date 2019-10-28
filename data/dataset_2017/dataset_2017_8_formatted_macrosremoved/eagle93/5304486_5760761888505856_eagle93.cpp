#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;
typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;

const int OO = (int)2e9;
const double eps = 1e-9;

const int N = 30;

int n, m;
char a[N][N];

void solve() {
  //  each char will take the whole row
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] != '?') {
        for (int k = j - 1; k >= 0; k--) {
          if (a[i][k] == '?') {
            a[i][k] = a[i][j];
          } else {
            break;
          }
        }
        for (int k = j + 1; k < m; k++) {
          if (a[i][k] == '?') {
            a[i][k] = a[i][j];
          } else {
            break;
          }
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (a[i][0] == '?') {
      for (int k = i - 1; k >= 0; k--) {
        if (a[k][0] != '?') {
          for (int j = 0; j < m; j++) {
            a[i][j] = a[k][j];
          }
          break;
        }
      }
      if (a[i][0] == '?') {
        for (int k = i + 1; k < n; k++) {
          if (a[k][0] != '?') {
            for (int j = 0; j < m; j++) {
              a[i][j] = a[k][j];
            }
            break;
          }
        }
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  //#ifndef ONLINE_JUDGE
  freopen("A-small-attempt1.in", "rt", stdin);
  freopen("out.txt", "wt", stdout);
  //#endif
  int t, tt = 1;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    solve();
    cout << "Case #" << tt++ << ":"
         << "\n";
    for (int i = 0; i < n; i++) {
      cout << a[i] << "\n";
    }
  }
  return 0;
}
