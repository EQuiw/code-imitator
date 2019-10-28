#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int a[6];
string s = "ROYGBV";

int main() {
  freopen("123.in", "r", stdin);
  freopen("123.out", "w", stdout);
  int T, cas = 0;
  cin >> T;
  while (T --) {
    int n;
    cin >> n;
    for (int i = 0; i < 6; i ++)
      cin >> a[i];
    string ans = "";
    int flag = 0;
    while (ans.size() < n) {
      int mx = 0, c = 0;
      for (int i = 0; i < 6; i ++) {
        if (s[i] == ans.back()) continue;
        if (a[i] == mx && ans.size() && s[i] == ans[0]) mx = a[i], c = i;
        if (a[i] > mx) mx = a[i], c = i;
      }
      if (s[c] == ans.back() || a[c] == 0) {
        flag = 1; break;
      }
      ans.push_back(s[c]);
      a[c] --;
    }
    // cout << ans << endl;
    if (ans.size() > 1 && ans[0] == ans.back())
      flag = 1;
    printf("Case #%d: ", ++ cas);
    if (flag)
      puts("IMPOSSIBLE");
    else
      printf("%s\n", ans.c_str());
  }
  return 0;
}