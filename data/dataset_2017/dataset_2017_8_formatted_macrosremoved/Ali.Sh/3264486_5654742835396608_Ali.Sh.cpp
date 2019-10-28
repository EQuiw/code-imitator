#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 1001 * 1001, MOD = 1e9 + 7;

set<pair<pair<long long, long long>, long long>> s;

int32_t main() {
  ios::sync_with_stdio(0);
  long long t;
  cin >> t;
  for (long long _ = 1; _ <= t; _++) {
    long long n, k;
    cin >> n >> k;
    s.clear();
    s.insert({{-((n - 1) / 2), -n}, 0});
    for (long long i = 0; i < k - 1; i++) {
      //		if(!s.size())
      //			cout << i << endl ;
      long long t = -s.begin()->first.second;
      long long j = s.begin()->second;
      s.erase(s.begin());
      //		if(n==1000) cout << t << ' ' << j << endl ;
      if (t == 1)
        continue;
      long long l = (t - 1) / 2, r = t / 2;
      if (l)
        s.insert({{-((l - 1) / 2), -l}, j});
      s.insert({{-((r - 1) / 2), -r}, j + l + 1});
    }
    long long x = -s.begin()->first.second;
    cout << "Case #" << _ << ": " << (x) / 2 << ' ' << (x - 1) / 2 << '\n';
  }
}
