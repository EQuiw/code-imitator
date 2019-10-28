#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef long long int tint;
typedef pair<int, int> par;

tint d[110][110];
int e[110];
int s[110];
par qu[110];

double dp[110][110];

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out2.txt", "w", stdout);

  int t, n, q;
  cin >> t;

  for (int caso = (1); caso < (t + 1); caso++) {
    cin >> n >> q;
    // cout << n << " " << q << endl;
    for (int i = 0; i < (n); i++)
      cin >> e[i + 1] >> s[i + 1];
    for (int i = 0; i < (n); i++) {
      for (int j = 0; j < (n); j++)
        cin >> d[i + 1][j + 1];
    }
    for (int i = 0; i < (q); i++) {
      cin >> qu[i].first >> qu[i].second;
    }
    tint acum[110];
    acum[1] = 0;
    for (int i = 0; i < (110); i++)
      for (int j = 0; j < (110); j++)
        dp[i][j] = -1;
    dp[2][1] = d[1][2] / (s[1] + 0.0);
    for (int i = (2); i < (n + 1); i++)
      acum[i] = acum[i - 1] + d[i - 1][i];
    // forn(i,n+1) cout << acum[i] << " ";
    // cout << endl;

    for (int i = (3); i < (n + 1); i++) {
      for (int j = (1); j < (i); j++) {
        tint dis = (acum[i] - acum[j]);
        if (dis <= e[j] and dis >= 0) {
          double t = dis / (s[j] + 0.0);
          double m = -1;
          for (int k = (1); k < (j); k++) {
            if (dp[j][k] >= 0.0) {
              if (m > -1)
                m = min(m, dp[j][k]);
              else
                m = dp[j][k];
            }
          }
          if (m >= 0)
            dp[i][j] = t + m;
        }
      }
    }
    double ans = -1;
    for (int i = (1); i < (n); i++) {
      if (dp[n][i] >= 0.0) {
        if (ans >= 0.0)
          ans = min(ans, dp[n][i]);
        else
          ans = dp[n][i];
      }
    }

    cout.setf(ios::showpoint | ios::fixed);
    cout.precision(10);

    cout << "Case #" << caso << ": " << ans << endl;
  }

  return 0;
}
