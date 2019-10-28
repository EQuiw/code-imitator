#include <bits/stdc++.h>
using namespace std;

void solve(int tt) {
  string s;
  int k;
  cin >> s;
  cin >> k;
  int ans = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '+')
      continue;
    if (i + k - 1 >= s.size()) {
      cout << "Case #" << tt << ": IMPOSSIBLE" << endl;
      return;
    }
    for (int j = i; j < i + k; j++) {
      if (s[j] == '+')
        s[j] = '-';
      else
        s[j] = '+';
    }
    ans++;
  }
  cout << "Case #" << tt << ": " << ans << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++)
    solve(i);
}
