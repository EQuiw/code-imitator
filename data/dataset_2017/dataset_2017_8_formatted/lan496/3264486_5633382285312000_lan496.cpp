#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(x) (x).begin(), (x).end()

typedef long long ll;
typedef long double ld;

const int INF = 1e9;
const ld EPS = 1e-8;

ll memo[20][10][2];
string N;

ll nCr(int n, int r) {
  if (n - r < r)
    return nCr(n, n - r);
  ll res = 1;
  REP(i, r) res *= n - i;
  REP(i, r) res /= i + 1;
  return res;
}

ll dp(int k, int x, int f) {
  if (memo[k][x][f] != -1)
    return memo[k][x][f];
  if (k == 0 && x == 0 && f == 0)
    return memo[k][x][f] = 0;

  ll res = 0;
  if (f == 1 && N.length() - k > 0) {
    res = nCr(9 - x + N.length() - k, 9 - x);
  } else {
    for (int i = max(1, x); i <= N[k]; ++i) {
      res += dp(k + 1, i, 1);
    }
    res += dp(k + 1, N[k], 0);
  }

  return memo[k][x][f] = res;
}

int main() {
  int T;
  cin >> T;
  REP(t, T) {
    cin >> N;
    REP(i, 20) REP(j, 10) REP(k, 2) memo[i][j][k] = -1;
    int d = N.length();
    ll res = dp(d, N[d - 1], 1);
    cout << "Case #" << t + 1 << ": " << res << endl;
  }
  return 0;
}
