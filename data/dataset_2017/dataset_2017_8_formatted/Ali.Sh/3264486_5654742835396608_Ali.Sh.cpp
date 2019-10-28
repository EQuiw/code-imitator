#include <bits/stdc++.h>

#define int long long
#define ll long long
#define F first
#define S second
#define pb push_back
#define ld double

using namespace std;

const int MAXN = 1001 * 1001, MOD = 1e9 + 7;

set<pair<pair<int, int>, int>> s;

int32_t main() {
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  for (int _ = 1; _ <= t; _++) {
    int n, k;
    cin >> n >> k;
    s.clear();
    s.insert({{-((n - 1) / 2), -n}, 0});
    for (int i = 0; i < k - 1; i++) {
      //		if(!s.size())
      //			cout << i << endl ;
      int t = -s.begin()->F.S;
      int j = s.begin()->S;
      s.erase(s.begin());
      //		if(n==1000) cout << t << ' ' << j << endl ;
      if (t == 1)
        continue;
      int l = (t - 1) / 2, r = t / 2;
      if (l)
        s.insert({{-((l - 1) / 2), -l}, j});
      s.insert({{-((r - 1) / 2), -r}, j + l + 1});
    }
    int x = -s.begin()->F.S;
    cout << "Case #" << _ << ": " << (x) / 2 << ' ' << (x - 1) / 2 << '\n';
  }
}
