#include <bits/stdc++.h>

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    string s;
    int k;
    cin >> s >> k;
    int ans = 0;
    for (int i = 0; i < s.size(); ++i)
      if (s[i] == '-') {
        if (i + k > s.size()) {
          ans = -1;
          break;
        }
        ans += 1;
        for (int j = i; j < i + k; ++j) {
          if (s[j] == '-')
            s[j] = '+';
          else
            s[j] = '-';
        }
      }
    cout << "Case #" << tc << ": ";
    if (ans != -1)
      cout << ans << endl;
    else
      cout << "IMPOSSIBLE" << endl;
  }
  return 0;
}