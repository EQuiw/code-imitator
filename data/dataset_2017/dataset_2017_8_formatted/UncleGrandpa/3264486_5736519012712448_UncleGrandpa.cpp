/*input
3
---+-++- 3
+++++ 4
-+-+- 4
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
#define sp ' '
#define endl '\n'
#define fi first
#define se second
#define mp make_pair
#define int long long
#define N 1005
string s;
int k;
bool a[N];
int ans = 0;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
#ifdef UncleGrandpa
  freopen("1test.inp", "r", stdin);
  freopen("1test.out", "w", stdout);
#endif
  int T;
  cin >> T;
  int ct = 0;
  while (T--) {
    ans = 0;
    ct++;
    cin >> s >> k;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '+')
        a[i + 1] = true;
      else
        a[i + 1] = false;
    }
    bool poss = true;
    for (int i = 1; i <= s.size(); i++) {
      if (a[i] == false) {
        if (i + k - 1 > s.size()) {
          poss = false;
          break;
        }
        for (int j = i; j <= i + k - 1; j++)
          a[j] = 1 - a[j];
        ans++;
      }
      // for (int i = 1; i <= s.size(); i++) cout << a[i] << sp;
      // cout << endl;
    }
    if (!poss) {
      cout << "Case #" << ct << ": "
           << "IMPOSSIBLE" << endl;
    } else
      cout << "Case #" << ct << ": " << ans << endl;
  }
}