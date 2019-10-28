#include <bits/stdc++.h>

using namespace std;

int a[50][1200000];
int b[50][1200000];
int y[50];
int cnt[50];
int u[50];
int n, p;

void solve() {
  cin >> n >> p;
  set<int> s;
  for (int i = 0; i < n; i++)
    cin >> y[i];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++) {
      int x;
      cin >> x;
      int n1 = lround(ceil((10.0 * x) / (11.0 * y[i])));
      int n2 = lround(floor((10.0 * x) / (9.0 * y[i])));
      if (n1 == 0)
        n1++;
      if (n1 > n2)
        continue;
      a[i][n1]++;
      b[i][n2 + 1]++;
      s.insert(n1);
      s.insert(n2);
    }
  }
  for (int i = 0; i < n; i++)
    u[i] = cnt[i] = 0;
  int ans = 0;
  for (int i : s) {
    int m = 1000000000;
    for (int j = 0; j < n; j++) {
      if (u[j] && b[j][i]) {
        if (u[j] > b[j][i]) {
          u[j] -= b[j][i];
          b[j][i] = 0;
        } else {
          b[j][i] -= u[j];
          u[j] = 0;
        }
      }
      cnt[j] += a[j][i];
      cnt[j] -= b[j][i];
      a[j][i] = b[j][i] = 0;
      m = min(m, cnt[j]);
    }
    if (m > 0) {
      ans += m;
      for (int j = 0; j < n; j++) {
        u[j] += m;
        cnt[j] -= m;
      }
    }
  }
  cout << ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    solve();
    cout << endl;
  }

  return 0;
}
