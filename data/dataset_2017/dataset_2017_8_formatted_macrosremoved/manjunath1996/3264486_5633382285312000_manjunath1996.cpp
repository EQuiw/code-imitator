#include <bits/stdc++.h>
using namespace std;
int main() {

  int tc, flag;
  long long ans = 0;
  string s;

  cin >> tc;
  for (int ca = 1; ca <= tc; ca++) {
    ans = 0;
    cin >> s;
    while (true) {
      flag = -1;
      for (int i = 0; i < s.length(); i++) {
        if (s[i] < s[i - 1]) {
          flag = i;
          break;
        }
      }
      if (flag == -1)
        break;
      s[flag - 1]--;
      for (int i = flag; i < s.length(); i++) {
        s[i] = '9';
      }
    }

    for (int i = 0; i < s.length(); i++) {
      ans = ans * 10LL + (s[i] - '0');
    }

    printf("Case #%d: %lld\n", ca, ans);
  }
}
