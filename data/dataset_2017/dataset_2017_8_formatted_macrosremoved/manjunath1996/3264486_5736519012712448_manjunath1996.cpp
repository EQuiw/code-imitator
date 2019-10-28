#include <bits/stdc++.h>
using namespace std;
int main() {

  int tc, cnt, flag, k;
  string s;
  cin >> tc;
  for (int ca = 1; ca <= tc; ca++) {
    cin >> s >> k;
    cnt = 0;
    flag = 0;

    for (int i = k - 1; i < s.length(); i++) {
      if (s[i - k + 1] == '-') {
        cnt++;
        for (int j = i - k + 1; j <= i; j++) {
          if (s[j] == '-')
            s[j] = '+';
          else
            s[j] = '-';
        }
      }
    }
    for (int i = s.length() - 1 - k + 1; i <= s.length() - 1; i++) {
      if (s[i] == '-')
        flag = 1;
    }

    printf("Case #%d: ", ca);
    if (flag == 1)
      cout << "IMPOSSIBLE\n";
    else
      cout << cnt << endl;
  }
}
