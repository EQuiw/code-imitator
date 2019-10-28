#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  string a[30];
  for (int i = 0; i < n; i++)
    cin >> a[i];
  int er = 0, ec = 0;
  bool r = false;
  for (int i = 0; i < n; i++) {
    char q = 0;
    for (int j = 0; j < m; j++)
      if (a[i][j] == '?') {
        if (q)
          a[i][j] = q;
      } else {
        if (!q) {

          for (int k = 0; k < j; k++)
            a[i][k] = a[i][j];
        }
        q = a[i][j];
      }
    if (!q) {
      if (r)
        a[i] = a[i - 1];
    } else {
      if (!r) {
        r = true;
        for (int k = 0; k < i; k++)
          a[k] = a[i];
      }
    }
  }
  for (int i = 0; i < n; i++)
    cout << a[i] << endl;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": " << endl;
    ;
    solve();
  }

  return 0;
}
