#include <bits/stdc++.h>
using namespace std;

int tc;

int main() {
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    string s;
    int k, fl = 0;
    cin >> s >> k;
    for (int i = 0; i < s.size() - k + 1; i++) {
      if (s[i] == '-') {
        // cout << "Flip at " << i << endl;
        fl++;
        for (int j = i; j < i + k; j++) {
          if (s[j] == '-')
            s[j] = '+';
          else
            s[j] = '-';
        }
      }
    }
    int f = 1;
    for (int i = s.size() - k + 1; i < s.size(); i++) {
      if (s[i] == '-')
        f = 0;
    }
    if (f == 1) {
      printf("Case #%d: %d\n", t, fl);
    } else {
      printf("Case #%d: IMPOSSIBLE\n", t, fl);
    }
  }
}
