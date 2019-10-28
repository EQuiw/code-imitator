#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("A.txt", "r", stdin);
  freopen("W.txt", "w", stdout);
  int t;
  cin >> t;
  int index = 1;
  while (t--) {
    string s;
    cin >> s;
    int k;
    cin >> k;
    int coun = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (i + k > s.size())
        break;
      if (s[i] == '+')
        continue;
      for (int j = 0; j < k; ++j) {
        if (s[i + j] == '+')
          s[i + j] = '-';
        else
          s[i + j] = '+';
      }
      ++coun;
    }
    // cout << s << endl;
    bool flag = 1;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '-') {
        flag = 0;
        break;
      }
    }
    if (!flag)
      cout << "Case #" << index++ << ": "
           << "IMPOSSIBLE" << endl;
    else
      cout << "Case #" << index++ << ": " << coun << endl;
  }
  return 0;
}
