#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  int t, cas = 1;
  cin >> t;
  while (t--) {
    cout << "Case #" << cas++ << ": ";
    string s, ans = "", pre = "", nine = "";
    cin >> s;
    if (s[0] != '1')
      ans += char(s[0] - 1);
    for (int i = 1, __ = s.size(); i < __; ++i) {
      ans += "9";
      nine += "9";
    }
    pre += s[0];
    int ok = 1;
    for (int i = 1, __ = s.size(); i < __; ++i) {
      if (s[i] < s[i - 1]) {
        ok = 0;
        break;
      }
      nine.pop_back();
      if (s[i] == s[i - 1]) {
        pre += s[i];
        continue;
      }
      ans = pre + char(s[i] - 1) + nine;
      pre += s[i];
    }
    if (ok)
      ans = s;
    cout << ans << endl;
  }
}
