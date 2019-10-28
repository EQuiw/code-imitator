#include <bits/stdc++.h>

using namespace std;

int k;
string s;
bool f[1010];

char flipped(char c) { return c == '-' ? '+' : '-'; }

int solve() {
  cin >> s >> k;
  int n = s.length();
  int ans = 0;
  bool flipping = false;
  for (int i = 0; i < n; i++)
    f[i] = false;
  for (int i = 0; i < n; i++) {
    if (f[i])
      flipping = !flipping;
    if (flipping)
      s[i] = flipped(s[i]);
    if (s[i] == '-') {
      if (i + k > n)
        return -1;
      f[i + k] = true;
      flipping = !flipping;
      s[i] = '+';
      ans++;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    int ans = solve();
    if (ans == -1)
      cout << "IMPOSSIBLE";
    else
      cout << ans;
    cout << endl;
  }

  return 0;
}
