#include <bits/stdc++.h>
using namespace std;

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
  for (int i = 0; i < (int)(r); i++)
    res *= n - i;
  for (int i = 0; i < (int)(r); i++)
    res /= i + 1;
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
  for (int t = 0; t < (int)(T); t++) {
    cin >> N;
    for (int i = 0; i < (int)(20); i++)
      for (int j = 0; j < (int)(10); j++)
        for (int k = 0; k < (int)(2); k++)
          memo[i][j][k] = -1;
    int d = N.length();
    ll res = dp(d, N[d - 1], 1);
    cout << "Case #" << t + 1 << ": " << res << endl;
  }
  return 0;
}
