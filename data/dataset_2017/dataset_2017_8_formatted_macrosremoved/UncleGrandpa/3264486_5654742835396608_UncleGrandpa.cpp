/*input
5
4 2
5 2
6 2
1000 1000
1000 1
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

long long n, k;
bool a[1005];

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  long long T;
  cin >> T;
  long long CT = 0;
  while (T--) {
    CT++;
    cin >> n >> k;
    memset(a, 0, sizeof(a));
    a[0] = a[n + 1] = true;
    while (k--) {
      pair<long long, long long> mdis = make_pair(-1, -1);
      long long mpos = 0;
      for (long long i = 1; i <= n; i++) {
        if (a[i] == 1)
          continue;
        pair<long long, long long> dis = make_pair(0, 0);
        for (long long j = i - 1; j >= 0; j--) {
          if (a[j] == 1) {
            dis.first = i - j;
            break;
          }
        }
        for (long long j = i + 1; j <= n + 1; j++) {
          if (a[j] == 1) {
            dis.second = j - i;
            break;
          }
        }
        dis.first--;
        dis.second--;
        if (min(mdis.first, mdis.second) < min(dis.first, dis.second)) {
          mdis = dis;
          mpos = i;
        } else if (min(mdis.first, mdis.second) == min(dis.first, dis.second)) {
          if (max(mdis.first, mdis.second) < max(dis.first, dis.second)) {
            mdis = dis;
            mpos = i;
          }
        }
      }
      if (k == 0) {
        cout << "Case #" << CT << ": " << max(mdis.first, mdis.second) << ' '
             << min(mdis.first, mdis.second) << '\n';
      }
      a[mpos] = true;
    }
    // for (int i = 1; i <= n; i++) cout << a[i] << sp;
    // cout << endl;
  }
}
