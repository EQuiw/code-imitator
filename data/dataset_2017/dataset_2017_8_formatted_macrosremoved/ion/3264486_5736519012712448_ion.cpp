/* ***************************************
Author        :Scau.ion
Created Time  :2017/04/08 09:41:22 UTC+8
File Name     :ion.cpp
*************************************** */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

char s[maxn];

int main() {
  freopen("A-small-attempt0(1).in", "r", stdin);
  ;
  freopen("A-small-attempt0(1).out", "w", stdout);
  ;
  ios::sync_with_stdio(0);
  cin.tie(0);
  ;
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    int k;
    cin >> s >> k;
    int n = strlen(s);
    int ans = 0;
    for (int j = 0; j <= n - k; ++j) {
      if (s[j] == '-') {
        ++ans;
        for (int l = 0; l < k; ++l) {
          if (s[j + l] == '-')
            s[j + l] = '+';
          else
            s[j + l] = '-';
        }
      }
    }
    bool flag = 1;
    for (int j = n - k + 1; j < n; ++j)
      if (s[j] == '-')
        flag = 0;
    cout << "Case #" << i << ": ";
    if (flag)
      cout << ans << endl;
    else
      cout << "IMPOSSIBLE" << endl;
  }
  return 0;
}
