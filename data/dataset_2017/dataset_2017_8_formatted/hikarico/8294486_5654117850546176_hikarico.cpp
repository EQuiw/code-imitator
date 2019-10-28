#include <bits/stdc++.h>
using namespace std;

int t, tc, n;
int r, o, y, g, b, v;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    cin >> r >> o >> y >> g >> b >> v;
    cout << "Case #" << ++tc << ": ";
    string ans;
    deque<pair<int, pair<int, char>>> v;
    if (r)
      v.push_back({r, {0, 'R'}});
    if (y)
      v.push_back({y, {0, 'Y'}});
    if (b)
      v.push_back({b, {0, 'B'}});
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i)
      v[i].second.first = i;
    ans += v.back().second.second;
    v.back().first--;
    if (v.back().first == 0)
      v.pop_back();
    while (v.size() > 0) {
      sort(v.begin(), v.end());
      while (v.size() > 0 && v.front().first == 0)
        v.pop_front();
      if (v.empty())
        break;
      int i;
      for (i = v.size() - 1; i >= 0; --i) {
        if (v[i].second.second != ans.back()) {
          ans.push_back(v[i].second.second);
          v[i].first -= 1;
          break;
        }
      }
      if (i < 0)
        break;
    }
    // cout << v.empty() << ' ' << ans << endl;
    if (!v.empty() || ans[0] == ans.back())
      cout << "IMPOSSIBLE\n";
    else
      cout << ans << "\n";
  }
}
