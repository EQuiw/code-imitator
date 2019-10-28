/*input
1
2457295734
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

string s;
string ans;
long long a[25];
long long n;

void back(long long pos, long long base, bool nine) {
  if (pos == n + 1) {
    while (ans[0] == '0')
      ans.erase(ans.begin());
    throw 1;
  }
  if (nine) {
    ans += "9";
    back(pos + 1, 0, 1);
  }
  for (long long i = a[pos]; i >= base; i--) {
    if (i == a[pos]) {
      ans += i + '0';
      back(pos + 1, i, 0);
      ans.pop_back();
    } else {
      ans += i + '0';
      back(pos + 1, i, 1);
      ans.pop_back();
    }
  }
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  freopen("1test.inp", "r", stdin);
  freopen("1test.out", "w", stdout);
  long long T;
  cin >> T;
  long long ct = 0;
  while (T--) {
    ct++;
    ans.clear();
    cin >> s;
    n = s.size();
    for (long long i = 0; i < s.size(); i++)
      a[i + 1] = s[i] - '0';
    try {
      back(1, 0, 0);
    } catch (...) {
      cout << "Case #" << ct << ": ";
      cout << ans << '\n';
    }
  }
}
