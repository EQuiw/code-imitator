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
typedef pair<tint, tint> par;

par pan[1100];
pair<tint, par> info[1100];

tint dp[1100][1100];

tint sq(tint a) { return ((a) * (a)); }

tint area(par a) {
  tint ans = sq(a.first) + 2l * a.first * a.second;

  return (ans);
}

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out2.txt", "w", stdout);

  int t, n, k;
  cin >> t;

  cout.setf(ios::showpoint | ios::fixed);
  cout.precision(10);

  for (int caso = (1); caso < (t + 1); caso++) {
    cin >> n >> k;
    for (int i = 0; i < (n); i++)
      for (int j = 0; j < (n); j++)
        dp[i][j] = 0;
    for (int i = 0; i < (n); i++)
      cin >> pan[i].first >> pan[i].second;
    sort(pan, pan + n);

    tint ans = 0ll;

    for (int i = 0; i < (n); i++)
      dp[i][1] = area(pan[i]);
    tint best[1100];
    tint be[1100];
    best[0] = dp[0][1] - sq(pan[0].first);
    for (int i = 1; i < n; i++) {
      tint cnd = (dp[i][1] - sq(pan[i].first));
      if (cnd > best[i - 1]) {
        best[i] = cnd;
      } else
        best[i] = best[i - 1];
    }

    for (int j = (2); j < (k + 1); j++) {
      dp[j - 1][j] = area(pan[j - 1]) + best[j - 2];
      be[j - 1] = dp[j - 1][j] - sq(pan[j - 1].first);
      // cout << dp[j-1][j] << " ";
      for (int i = j; i < n; i++) {
        dp[i][j] = area(pan[i]) + best[i - 1];
        tint cnd = dp[i][j] - sq(pan[i].first);
        if (cnd > be[i - 1])
          be[i] = cnd;
        else
          be[i] = be[i - 1];
        // cout << dp[i][j] << " ";
      }
      for (int i = 0; i < (n); i++)
        best[i] = be[i];
    }
    for (int i = 0; i < (n); i++) {
      ans = max(dp[i][k], ans);
    }

    cout << "Case #" << caso << ": " << ans * acos(-1) << endl;
  }

  return 0;
}
