/* ***************************************
Author        :Scau.ion
Created Time  :2017/04/23 00:23:02 UTC+8
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
    int n;
    cin >> n;
    pair<int, char> a[3];
    for (int j = 0; j < 3; ++j) {
      cin >> a[j].first;
      int xx;
      cin >> xx;
    }
    a[0].second = 'R';
    a[1].second = 'Y';
    a[2].second = 'B';
    sort(a, a + 3);
    cout << "Case #" << i << ": ";
    if (a[2].first > a[0].first + a[1].first)
      cout << "IMPOSSIBLE" << endl;
    else {
      vector<char> ans;
      for (int j = 1; j <= a[2].first; ++j)
        ans.push_back(a[2].second);
      int st = 0;
      for (int j = 1; j <= a[1].first; ++j) {
        ans.insert(ans.begin() + st, a[1].second);
        st += 2;
      }
      int j;
      for (j = 1; j <= a[0].first; ++j) {
        if (st == ans.size())
          break;
        ans.insert(ans.begin() + st, a[0].second);
        st += 2;
      }
      st = 0;
      for (; j <= a[0].first; ++j) {
        ans.insert(ans.begin() + st, a[0].second);
        st += 2;
      }
      for (int j = 0; j < ans.size(); ++j)
        cout << ans[j];
      cout << endl;
    }
  }
  return 0;
}
