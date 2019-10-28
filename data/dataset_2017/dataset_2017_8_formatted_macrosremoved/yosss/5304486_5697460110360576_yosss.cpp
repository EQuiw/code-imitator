#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, long long> pll;
const long long MODP = 1000000007;

long long n, p;
long long r[50];
long long q[50][50];
long long mini[50][50], maxi[50][50];

bool ok(pll x, pll y) {
  return (max(x.first, y.first) < min(x.second, y.second));
}

void solve(void) {
  cin >> n >> p;
  for (int i = 0; i < n; i++)
    cin >> r[i];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < p; j++)
      cin >> q[i][j];
  for (int i = 0; i < n; i++)
    sort(&q[i][0], &q[i][p]);

  vector<vector<pll>> range(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++) {
      mini[i][j] = (q[i][j] * 10 + r[i] * 11 - 1) / (r[i] * 11);
      maxi[i][j] = (q[i][j] * 10) / (r[i] * 9);
      if (mini[i][j] >= 1 && mini[i][j] <= maxi[i][j]) {
        range[i].push_back(make_pair(mini[i][j], maxi[i][j] + 1));
        // cout << mini[i][j] << "-" << maxi[i][j] << "\t";
      } // else cout << "x-x" << "\t";
    }
    // cout << endl;
  }
  long long ans = 0;
  if (n == 1) {
    ans = range[0].size();
  } else if (n == 2) {
    // greedy
    long long offs = 0;
    for (int i = 0; i < range[0].size(); i++) {
      for (int j = offs; j < range[1].size(); j++) {
        if (ok(range[0][i], range[1][j])) {
          ans++;
          offs = j + 1;
          break;
        }
      }
    }
  }
  cout << ans << endl;
  return;
}

int main(void) {
  int T;
  cin >> T;
  for (int tcnt = 1; tcnt <= T; tcnt++) {
    cout << "Case #" << tcnt << ": ";
    solve();
  }
  return 0;
}
