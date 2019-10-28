#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    string s;
    int k;
    cin >> s >> k;
    int ans = 0;
    cout << "Case #" << i << ": ";
    for (int i = 0; i <= s.size() - k; ++i) {
      if (s[i] == '+')
        continue;
      ++ans;
      for (int j = i; j < i + k; ++j) {
        if (s[j] == '-')
          s[j] = '+';
        else
          s[j] = '-';
      }
    }
    bool fl = 1;
    for (int i = 0; i < s.size(); ++i)
      fl &= (s[i] == '+');
    if (!fl)
      cout << "IMPOSSIBLE\n";
    else
      cout << ans << "\n";
  }
  return 0;
}
