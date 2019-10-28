/* ***************************************
Author        :Scau.ion
Created Time  :2017/04/15 08:49:04 UTC+8
File Name     :ion.cpp
*************************************** */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 30;

char s[maxn][maxn];
bool have[maxn];

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  ;
  freopen("A-small-attempt0.out", "w", stdout);
  ;
  ios::sync_with_stdio(0);
  cin.tie(0);
  ;
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    int r, c;
    cin >> r >> c;
    memset(have, 0, sizeof have);
    for (int j = 1; j <= r; ++j) {
      cin >> (s[j] + 1);
      for (int k = 1; k <= c; ++k)
        if (s[j][k] != '?')
          have[j] = 1;
    }
    for (int j = 1; j <= r; ++j) {
      for (int k = 1; k < c; ++k)
        if (s[j][k] != '?' && s[j][k + 1] == '?')
          s[j][k + 1] = s[j][k];
      for (int k = c; k > 1; --k)
        if (s[j][k] != '?' && s[j][k - 1] == '?')
          s[j][k - 1] = s[j][k];
    }
    for (int j = 1; j < r; ++j) {
      if (have[j] == 1 && have[j + 1] == 0) {
        have[j + 1] = 1;
        for (int k = 1; k <= c; ++k)
          s[j + 1][k] = s[j][k];
      }
    }
    for (int j = r; j > 1; --j) {
      if (have[j] == 1 && have[j - 1] == 0) {
        have[j - 1] = 1;
        for (int k = 1; k <= c; ++k)
          s[j - 1][k] = s[j][k];
      }
    }
    cout << "Case #" << i << ":\n";
    for (int j = 1; j <= r; ++j)
      cout << (s[j] + 1) << "\n";
  }
  cout << flush;
  return 0;
}
