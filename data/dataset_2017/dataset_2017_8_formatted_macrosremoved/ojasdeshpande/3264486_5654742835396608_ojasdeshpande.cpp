#include <bits/stdc++.h>

using namespace std;

signed main() {
  freopen("a.txt", "r", stdin);
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long tt;
  cin >> tt;
  for (long long t = 1; t <= tt; t++) {
    cout << "Case #" << t << ": ";
    long long n, k;
    cin >> n >> k;
    set<pair<long long, long long>> s;
    s.insert({n, 1});
    long long cur = 0;
    while (1) {
      auto it = s.end();
      it--;
      pair<long long, long long> p = *it;
      s.erase(it);
      long long a = (p.first - 1) / 2;
      long long b = a;
      if (p.first % 2 == 0)
        b = a + 1;
      if (cur + p.second >= k) {
        cout << b << " " << a << "\n";
        break;
      }
      it = s.lower_bound({a, 0});
      if (it != s.end() && it->first == a) {
        pair<long long, long long> q = {a, it->second + p.second};
        s.erase(it);
        s.insert(q);
      } else {
        s.insert({a, p.second});
      }
      it = s.lower_bound({b, 0});
      if (it != s.end() && it->first == b) {
        pair<long long, long long> q = {b, it->second + p.second};
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
