#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MOD 1000000007

signed main() {
  freopen("a.txt", "r", stdin);
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int t = 1; t <= tt; t++) {
    cout << "Case #" << t << ": ";
    int n, k;
    cin >> n >> k;
    set<pair<int, int>> s;
    s.insert({n, 1});
    int cur = 0;
    while (1) {
      auto it = s.end();
      it--;
      pair<int, int> p = *it;
      s.erase(it);
      int a = (p.first - 1) / 2;
      int b = a;
      if (p.first % 2 == 0)
        b = a + 1;
      if (cur + p.second >= k) {
        cout << b << " " << a << "\n";
        break;
      }
      it = s.lower_bound({a, 0});
      if (it != s.end() && it->first == a) {
        pair<int, int> q = {a, it->second + p.second};
        s.erase(it);
        s.insert(q);
      } else {
        s.insert({a, p.second});
      }
      it = s.lower_bound({b, 0});
      if (it != s.end() && it->first == b) {
        pair<int, int> q = {b, it->second + p.second};
        s.erase(it);
        s.insert(q);
      } else {
        s.insert({b, p.second});
      }
      cur += p.second;
    }
  }
  return 0;
}