#include <bits/stdc++.h>

#define int long long
#define ll long long
#define F first
#define S second
#define pb push_back
#define ld double

using namespace std;

const int MAXN = 55, MOD = 1e9 + 7;

int need[MAXN];

deque<int> a[MAXN];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    cin >> need[i];
  for (int i = 0; i < MAXN; i++)
    a[i].clear();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      int x;
      cin >> x;
      a[i].pb(x);
    }
  for (int i = 0; i < n; i++)
    sort(a[i].begin(), a[i].end());
  int ans = 0;
  while (1) {
    bool f = 0;
    for (int i = 0; i < n; i++)
      if (!a[i].size())
        f = 1;
    if (f)
      break;
    pair<int, int> mnR = {1e9, 1};
    for (int i = 0; i < n; i++) {
      int y = a[i].front();
      int x = 9 * need[i] / 10;
      if (!x)
        continue;
      int r = (y) / x;
      if (!i)
        mnR = {r, i};
      mnR = min(mnR, {r, i});
      //		cout << '*' << i << ' ' << r << ' ' << x * r << '\n' ;
    }
    int mxL = -1;
    for (int i = 0; i < n; i++) {
      int y = a[i].front();
      int x = 11 * need[i] / 10;
      if (!x)
        continue;
      int l = (y + x - 1) / x;
      mxL = max(mxL, l);
    }
    //	cout << mxL << ' ' << mnR.F << '\n' ;
    if (mxL <= mnR.F) {
      ans++;
      for (int i = 0; i < n; i++)
        a[i].pop_front();
    } else
      a[mnR.S].pop_front();
  }
  cout << ans << '\n';
}

int32_t main() {
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  for (int _ = 1; _ <= t; _++) {
    cout << "Case #" << _ << ": ";
    solve();
  }
}
