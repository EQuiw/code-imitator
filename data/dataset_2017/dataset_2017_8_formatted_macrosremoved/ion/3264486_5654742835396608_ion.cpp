/* ***************************************
Author        :Scau.ion
Created Time  :2017/04/08 18:38:40 UTC+8
File Name     :ion.cpp
*************************************** */

#include <bits/stdc++.h>
using namespace std;
int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  ;
  freopen("C-small-1-attempt0.out", "w", stdout);
  ;
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    long long n, k;
    cin >> n >> k;
    map<long long, long long> mp;
    mp[n] = 1;
    queue<long long> que;
    que.push(n);
    while (1) {
      long long tis = que.front();
      que.pop();
      long long num = mp[tis];
      if (num >= k) {
        cout << "Case #" << i << ": " << (tis / 2) << " " << ((tis - 1) / 2)
             << endl;
        break;
      }
      k -= num;
      if (mp.find(tis / 2) == mp.end())
        que.push(tis / 2);
      if (tis % 2 == 0 && mp.find((tis - 1) / 2) == mp.end())
        que.push((tis - 1) / 2);
      mp[tis / 2] += num;
      mp[(tis - 1) / 2] += num;
    }
  }
}
