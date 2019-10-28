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
#define sp ' '
#define endl '\n'
#define fi first
#define se second
#define mp make_pair
#define int long long
#define N 1005
int n, k;
bool a[N];

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
#ifdef UncleGrandpa
  freopen("1test.inp", "r", stdin);
  freopen("1test.out", "w", stdout);
#endif
  int T;
  cin >> T;
  int CT = 0;
  while (T--) {
    CT++;
    cin >> n >> k;
    memset(a, 0, sizeof(a));
    a[0] = a[n + 1] = true;
    while (k--) {
      pair<int, int> mdis = mp(-1, -1);
      int mpos = 0;
      for (int i = 1; i <= n; i++) {
        if (a[i] == 1)
          continue;
        pair<int, int> dis = mp(0, 0);
        for (int j = i - 1; j >= 0; j--) {
          if (a[j] == 1) {
            dis.fi = i - j;
            break;
          }
        }
        for (int j = i + 1; j <= n + 1; j++) {
          if (a[j] == 1) {
            dis.se = j - i;
            break;
          }
        }
        dis.fi--;
        dis.se--;
        if (min(mdis.fi, mdis.se) < min(dis.fi, dis.se)) {
          mdis = dis;
          mpos = i;
        } else if (min(mdis.fi, mdis.se) == min(dis.fi, dis.se)) {
          if (max(mdis.fi, mdis.se) < max(dis.fi, dis.se)) {
            mdis = dis;
            mpos = i;
          }
        }
      }
      if (k == 0) {
        cout << "Case #" << CT << ": " << max(mdis.fi, mdis.se) << sp
             << min(mdis.fi, mdis.se) << endl;
      }
      a[mpos] = true;
    }
    // for (int i = 1; i <= n; i++) cout << a[i] << sp;
    // cout << endl;
  }
}