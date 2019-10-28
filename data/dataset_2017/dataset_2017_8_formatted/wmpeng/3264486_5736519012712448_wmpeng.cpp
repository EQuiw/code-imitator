#include <iostream>
#include <stdio.h>
#include <string>
//#include<bits/stdc++.h>
using namespace std;
int main() {
  freopen("A-small-attempt1.in", "r", stdin);
  freopen("Qualification.out", "w", stdout);
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) // 100
  {
    int ans = 0, k;
    string pancake;
    cin >> pancake >> k;
    int length = pancake.length();

    for (int j = 0; j <= length - k; j++) // 1000
      if (pancake[j] == '-') {
        ans++;
        for (int ii = 0; ii < k; ii++) // 1000
          pancake[j + ii] = 88 - pancake[j + ii];
      }

    for (int j = length - k + 1; j < length; j++)
      if (pancake[j] == '-')
        ans = -1;
    cout << "Case #" << i + 1 << ": ";
    if (ans == -1)
      cout << "IMPOSSIBLE" << endl;
    else
      cout << ans << endl;
  }
  return 0;
}
