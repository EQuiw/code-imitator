#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 55, MOD = 1e9 + 7;

long long need[MAXN];

deque<long long> a[MAXN];

void solve() {
  long long n, m;
  cin >> n >> m;
  for (long long i = 0; i < n; i++)
    cin >> need[i];
  for (long long i = 0; i < MAXN; i++)
    a[i].clear();
  for (long long i = 0; i < n; i++)
    for (long long j = 0; j < m; j++) {
      long long x;
      cin >> x;
      a[i].push_back(x);
    }
  for (long long i = 0; i < n; i++)
    sort(a[i].begin(), a[i].end());
  long long ans = 0;
  while (1) {
    bool f = 0;
    for (long long i = 0; i < n; i++)
      if (!a[i].size())
        f = 1;
    if (f)
      break;
    pair<long long, long long> mnR = {1e9, 1};
    for (long long i = 0; i < n; i++) {
      long long y = a[i].front();
      long long x = 9 * need[i] / 10;
      if (!x)
        continue;
      long long r = (y) / x;
      if (!i)
        mnR = {r, i};
      mnR = min(mnR, {r, i});
      //		cout << '*' << i << ' ' << r << ' ' << x * r << '\n' ;
    }
    long long mxL = -1;
    for (long long i = 0; i < n; i++) {
      long long y = a[i].front();
      long long x = 11 * need[i] / 10;
      if (!x)
        continue;
      long long l = (y + x - 1) / x;
      mxL = max(mxL, l);
    }
    //	cout << mxL << ' ' << mnR.F << '\n' ;
    if (mxL <= mnR.first) {
      ans++;
      for (long long i = 0; i < n; i++)
        a[i].pop_front();
    } else
      a[mnR.second].pop_front();
  }
  cout << ans << '\n';
}

int32_t main() {
  ios::sync_with_stdio(0);
  long long t;
  cin >> t;
  for (long long _ = 1; _ <= t; _++) {
    cout << "Case #" << _ << ": ";
    solve();
  }
}
