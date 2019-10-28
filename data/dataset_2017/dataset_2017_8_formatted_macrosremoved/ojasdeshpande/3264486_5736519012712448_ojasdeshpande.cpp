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
    long long k;
    cin >> k;
    long long res = 0;
    bool f = false;
    for (long long i = 0; i < s.length(); i++) {
      if (s[i] == '-') {
        if (i + k > s.length()) {
          f = true;
          break;
        }
        for (long long j = i; j < i + k; j++) {
          if (s[j] == '-')
            s[j] = '+';
          else
            s[j] = '-';
        }
        res++;
      }
    }
    if (f)
      cout << "IMPOSSIBLE\n";
    else
      cout << res << "\n";
  }
  return 0;
}
