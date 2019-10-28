#include <bits/stdc++.h>

using namespace std;

int t;

void solve() {
  string s;
  int x;
  cin >> s >> x;
  int cnt = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '-' && i + x <= s.size()) {
      for (int j = i; j < i + x; j++)
        s[j] = (s[j] == '-' ? '+' : '-');
      cnt++;
      // cerr << "STRING AFTER: " << s << endl;
    }
  }
  for (char i : s) {
    if (i == '-') {
      cout << "IMPOSSIBLE\n";
      return;
    }
  }
  cout << cnt << '\n';
}

int main() {
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
}
