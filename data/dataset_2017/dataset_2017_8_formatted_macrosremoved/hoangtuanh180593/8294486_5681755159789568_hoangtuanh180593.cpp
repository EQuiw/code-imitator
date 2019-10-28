#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int mn = 107;

void mf() {
  // freopen("input.in","r",stdin);
  // return;
  freopen("Csmall3.in", "r", stdin);
  freopen("Csmall3.ou", "w", stdout);

  // freopen("Clarge.in","r",stdin);
  // freopen("Clarge.ou","w",stdout);
}
double a[mn], b[mn];
double f[mn][mn], d[mn][mn];
int n, s, t, q;
void solve() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      cin >> d[i][j];
      if (d[i][j] == -1)
        d[i][j] = 1e15;
      if (i == j)
        d[i][j] = 0;
    }
  cin >> s >> t;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      f[i][j] = 1e15;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      d[i][j] = d[j][i] = d[i][j - 1] + d[j - 1][j];
    }
  }
  ////

  f[1][1] = 0;
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (d[j][i] <= a[j]) {
        f[i][j] = min(f[i][j], f[i - 1][j] + d[i - 1][i] / b[j]);
        f[i][i] = min(f[i][i], f[i][j]);
      }
    }
    // d[i][i]
  }
  cout << setprecision(9) << fixed;
  cout << f[n][n] << endl;
}

int main() {
  ios_base::sync_with_stdio(false);

  int ntest;
  cin >> ntest;
  for (int nt = 1; nt <= ntest; nt++) {
    cout << "Case #" << nt << ": ";
    solve();
  }

  return 0;
}
