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
    string s;
    cin >> s;
    for (long long i = 0; i < 20; i++) {
      for (long long i = 0; i < s.length() - 1; i++) {
        if (s[i] > s[i + 1]) {
          s[i] -= 1;
          for (long long j = i + 1; j < s.length(); j++)
            s[j] = '9';
          break;
        }
      }
    }
    long long i = 0;
    for (; i < s.length(); i++)
      if (s[i] != '0')
        break;
    for (; i < s.length(); i++)
      cout << s[i];
    cout << "\n";
  }
  return 0;
}
