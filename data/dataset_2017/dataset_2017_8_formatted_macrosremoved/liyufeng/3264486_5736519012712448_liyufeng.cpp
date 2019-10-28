#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
const int INF = 0x7fffffff;
const long long INFF = 0x7fffffffffffffff;
const double pi = 3.141592653589793;
const double inf = 1e18;
const double eps = 1e-8;
const long long mod = 1e9 + 7;
/*************************************************************/
int ans = 0;
string str;
int k;
void solve() {
  int len = str.length();
  for (int i = 0; i < len; i++) {
    if (str[i] == '-') {
      if (i + k > len) {
        ans = -1;
        break;
      }
      ans++;
      for (int j = 0; j < k; j++) {
        if (str[i + j] == '-')
          str[i + j] = '+';
        else
          str[i + j] = '-';
      }
    }
  }
}
int main() {
  freopen("A-small-attempt5.in", "r", stdin);
  freopen("A-small-attempt5.out", "w", stdout);
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    ans = 0;
    cin >> str >> k;
    solve();
    if (ans == -1)
      printf("Case #%d: IMPOSSIBLE\n", i, ans);
    else
      printf("Case #%d: %d\n", i, ans);
  }
  fclose(stdin);
  fclose(stdout);

  return 0;
}
