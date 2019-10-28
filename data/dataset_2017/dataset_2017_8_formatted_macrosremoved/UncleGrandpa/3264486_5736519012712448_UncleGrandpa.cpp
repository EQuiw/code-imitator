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

string s;
long long k;
bool a[1005];
long long ans = 0;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  long long T;
  cin >> T;
  long long ct = 0;
  while (T--) {
    ans = 0;
    ct++;
    cin >> s >> k;
    for (long long i = 0; i < s.size(); i++) {
      if (s[i] == '+')
        a[i + 1] = true;
      else
        a[i + 1] = false;
    }
    bool poss = true;
    for (long long i = 1; i <= s.size(); i++) {
      if (a[i] == false) {
        if (i + k - 1 > s.size()) {
          poss = false;
          break;
        }
        for (long long j = i; j <= i + k - 1; j++)
          a[j] = 1 - a[j];
        ans++;
      }
      // for (int i = 1; i <= s.size(); i++) cout << a[i] << sp;
      // cout << endl;
    }
    if (!poss) {
      cout << "Case #" << ct << ": "
           << "IMPOSSIBLE" << '\n';
    } else
      cout << "Case #" << ct << ": " << ans << '\n';
  }
}
