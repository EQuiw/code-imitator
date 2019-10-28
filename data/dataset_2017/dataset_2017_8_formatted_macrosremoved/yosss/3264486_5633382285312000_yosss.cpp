#include <bits/stdc++.h>
using namespace std;

const long long MODP = 1000000007;

void solve(void) {
  string s;
  cin >> s;
  for (int i = 0; i + 1 < s.size(); i++) {
    if (s[i] > s[i + 1]) {
      int offs = i;
      for (; offs > 0; offs--) {
        if (s[offs - 1] < s[offs])
          break;
      }
      s[offs]--;
      for (int j = offs + 1; j < s.size(); j++) {
        s[j] = '9';
      }
      if (s[0] == '0')
        cout << s.substr(1);
      else
        cout << s;
      return;
    }
  }
  cout << s;
  return;
}

int main(void) {
  int T;
  cin >> T;
  for (int tcnt = 1; tcnt <= T; tcnt++) {
    cout << "Case #" << tcnt << ": ";
    solve();
    cout << endl;
  }
  return 0;
}
