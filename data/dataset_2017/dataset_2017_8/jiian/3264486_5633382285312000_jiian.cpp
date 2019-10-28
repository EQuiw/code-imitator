#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
  freopen("123.in", "r", stdin);
  freopen("123.out", "w", stdout);
  int T, cas = 0;
  cin >> T;
  while (T --) {
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    int n = s.size();
    for (int i = 1; i < n; i ++) {
      if (s[i] <= s[i - 1]) continue;
      for (int j = 0; j < i; j ++)
        s[j] = '9';
      int j = i;
      while (s[j] == '0')
        s[j] = '9', j ++;
      s[j] --;
    }
    while (s.back() == '0') s.pop_back();
    reverse(s.begin(), s.end());
    printf("Case #%d: %s\n", ++ cas, s.c_str());
  }
  return 0;
}