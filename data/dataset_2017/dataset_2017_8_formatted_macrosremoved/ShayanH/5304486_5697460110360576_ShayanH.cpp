#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const int MAXN = 1 * 100 + 10;

int r[MAXN];
int q[MAXN][MAXN];
set<pair<pii, int>> s[MAXN];

int main() {
  ios::sync_with_stdio(false);

  int tc;
  cin >> tc;
  for (int tt = 1; tt <= tc; tt++) {
    for (int i = 0; i < (MAXN); i++)
      s[i].clear();
    cout << "Case #" << tt << ": ";

    int n, p;
    cin >> n >> p;
    for (int i = 0; i < n; i++)
      cin >> r[i];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < p; j++)
        cin >> q[i][j];

    for (int i = 0; i < n; i++)
      for (int j = 0; j < p; j++) {
        int k1 = ceil((double)q[i][j] / ((double)r[i] * 1.1));
        int k2 = floor((double)q[i][j] / ((double)r[i] * 0.9));

        if (k1 <= k2)
          s[i].insert(make_pair(make_pair(k1, k2), j));
      }

    int ans = 0;
    while (((int)(s[0]).size())) {
      pair<pii, int> tmp = *s[0].begin();
      s[0].erase(s[0].begin());
      int k1 = tmp.first.first, k2 = tmp.first.second;

      bool check = true;
      for (int i = 1; i < n; i++) {
        if (s[i].empty())
          check = false;

        while (((int)(s[i]).size())) {
          pair<pii, int> tmp = *s[i].begin();
          int t1 = tmp.first.first, t2 = tmp.first.second;
          if (t2 < k1) {
            s[i].erase(s[i].begin());
            if (s[i].empty())
              check = false;
            continue;
          }
          k1 = max(k1, t1);
          k2 = min(k2, t2);
          break;
        }
      }
      if (k1 <= k2 && check) {
        for (int i = 1; i < n; i++)
          s[i].erase(s[i].begin());
        ans++;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
