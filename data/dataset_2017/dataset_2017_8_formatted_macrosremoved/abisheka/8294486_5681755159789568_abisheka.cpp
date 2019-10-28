#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef long double ld;
typedef vector<vector<ll>> mat;

ld mx = 1e18 + 7;

int main() {
  ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, t1 = 0;
  cin >> t;
  while (t--) {
    t1++;
    cout << "Case #";
    cout << t1;
    cout << ": ";
    int n, q;
    cin >> n >> q;
    ll e[105], s[105];
    for (int i = 0; i <= n - 1; i++)
      cin >> e[i] >> s[i];
    ll d[105][105], dd[105][105];
    for (int i = 0; i <= n - 1; i++)
      for (int j = 0; j <= n - 1; j++) {
        cin >> d[i][j];
        dd[i][j] = d[i][j];
        if (d[i][j] == -1)
          dd[i][j] = mx;
      }
    for (int i = 0; i <= n - 1; i++)
      dd[i][i] = 0;
    for (int k = 0; k <= n - 1; k++)
      for (int i = 0; i <= n - 1; i++)
        for (int j = 0; j <= n - 1; j++)
          dd[i][j] = min(dd[i][j], dd[i][k] + dd[k][j]);
    int to[105][105] = {0};
    for (int i = 0; i <= n - 1; i++) {
      for (int j = 0; j <= n - 1; j++) {
        if (dd[i][j] > e[i])
          to[i][j] = 0;
        else
          to[i][j] = 1;
      }
    }

    while (q--) {
      int l, r;
      cin >> l >> r;
      l--;
      r--;
      priority_queue<pair<ld, pair<int, int>>> q;
      ld dis[105][105];
      for (int i = 0; i <= n - 1; i++)
        for (int j = 0; j <= n - 1; j++)
          dis[i][j] = mx;
      dis[l][l] = 0;
      q.push(make_pair(0, make_pair(l, l)));
      while (!q.empty()) {

        int at = q.top().second.first, hor = q.top().second.second;
        ld d1 = -q.top().first;
        q.pop();
        if (d1 > dis[at][hor])
          continue;
        for (int i = 0; i <= n - 1; i++) {
          if (i == at)
            continue;
          if (d[at][i] == -1)
            continue;
          if (to[hor][i] == 0)
            continue;
          ld time = d[at][i];
          time /= (ld)s[hor];
          if (dis[at][hor] + time < dis[i][hor]) {
            dis[i][hor] = dis[at][hor] + time;
            q.push(make_pair(-dis[i][hor], make_pair(i, hor)));
          }
        }
        ld d2 = mx;
        for (int i = 0; i <= n - 1; i++)
          d2 = min(d2, dis[at][i]);
        for (int i = 0; i <= n - 1; i++) {
          if (i == at)
            continue;
          if (d[at][i] == -1)
            continue;
          if (to[at][i] == 0)
            continue;
          ld time = d[at][i];
          time /= (ld)s[at];
          if (d2 + time < dis[i][at]) {
            dis[i][at] = d2 + time;
            q.push(make_pair(-dis[i][at], make_pair(i, at)));
          }
        }
      }
      ld ans = mx;
      for (int i = 0; i <= n - 1; i++)
        ans = min(ans, dis[r][i]);
      cout << fixed << setprecision(10) << ans << " ";
    }
    cout << "\n";
  }
  return 0;
}
