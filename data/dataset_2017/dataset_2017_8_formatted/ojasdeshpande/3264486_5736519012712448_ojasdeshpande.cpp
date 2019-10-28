#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MOD 1000000007

signed main() {
  freopen("a.txt", "r", stdin);
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int t = 1; t <= tt; t++) {
    cout << "Case #" << t << ": ";
    string s;
    cin >> s;
    int k;
    cin >> k;
    int res = 0;
    bool f = false;
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '-') {
        if (i + k > s.length()) {
          f = true;
          break;
        }
        for (int j = i; j < i + k; j++) {
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