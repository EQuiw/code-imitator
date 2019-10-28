/* ***************************************
Author        :Scau.ion
Created Time  :2017/04/08 09:41:22 UTC+8
File Name     :ion.cpp
*************************************** */

#include <bits/stdc++.h>
using namespace std;
int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  ;
  freopen("B-small-attempt0.out", "w", stdout);
  ;
  ios::sync_with_stdio(0);
  cin.tie(0);
  ;
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    string s;
    cin >> s;
    int dec = -1;
    for (int j = 0; j < s.size() - 1; ++j) {
      if (s[j] > s[j + 1]) {
        dec = j;
        break;
      }
    }
    if (dec != -1) {
      while (dec >= 0 && s[dec] > s[dec + 1]) {
        --s[dec];
        --dec;
      }
      for (int j = dec + 2; j < s.size(); ++j)
        s[j] = '9';
    }
    while (s[0] == '0')
      s.erase(0, 1);
    cout << "Case #" << i << ": " << s << endl;
  }
  return 0;
}
