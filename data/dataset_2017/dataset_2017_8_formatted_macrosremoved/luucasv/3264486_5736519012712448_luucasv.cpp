#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  int t, cas = 1;
  cin >> t;
  while (t--) {
    cout << "Case #" << cas++ << ": ";
    string s;
    int k;
    cin >> s >> k;
    vector<int> v(s.size(), 0);
    for (int i = 0, __ = s.size(); i < __; ++i) {
      v[i] = s[i] == '+';
    }
    int ans = 0, ok = 1;
    for (int i = 0, __ = v.size(); i < __; ++i) {
      if (v[i])
        continue;
      if (i + k > v.size()) {
        ok = 0;
        break;
      }
      ++ans;
      for (int j = 0, __ = k; j < __; ++j) {
        v[i + j] = 1 - v[i + j];
      }
    }
    if (ok)
      cout << ans << endl;
    else
      cout << "IMPOSSIBLE" << endl;
  }
}
