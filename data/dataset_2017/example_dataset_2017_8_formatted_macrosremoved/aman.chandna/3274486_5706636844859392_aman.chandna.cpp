

#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// struct my {
//	ll start,end;
//	bool iscam;
//};

int main() {

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  freopen("inp2.txt", "r", stdin);
  freopen("out2.txt", "w", stdout);
  long long t;
  cin >> t;
  for (long long ccr = 1; ccr <= t; ++ccr) {
    long long ans = 0;
    long long ac, aj;
    cin >> ac >> aj;
    vector<pair<long long, long long>> c(ac, {0.0, 0.0}), j(aj, {0.0, 0.0});

    for (long long i = 0; i < ac; ++i)
      cin >> c[i].first >> c[i].second;
    for (long long i = 0; i < aj; ++i)
      cin >> j[i].first >> j[i].second;
    sort(j.begin(), j.end());
    sort(c.begin(), c.end());
    if (aj == 0 && ac == 1 || aj == 1 && ac == 0)
      ans = 2;
    else if (ac == 0) {
      ans = 4;
      if (j[1].second - j[0].first <= 720) {
        ans = 2;
      }
      long long val = 1440 - j[1].first + j[0].second;
      if (val <= 720) {
        ans = 2;
      }
    } else if (aj == 0 && ac == 2) {
      ans = 4;
      if (c[1].second - c[0].first <= 720) {
        ans = 2;
      }
      long long val = 1440 - c[1].first + c[0].second;
      if (val <= 720) {
        ans = 2;
      }
    } else {
      ans = 2;
    }
    cout << "Case #" << ccr << ": " << ans << "\n";
  }

  return 0;
}
