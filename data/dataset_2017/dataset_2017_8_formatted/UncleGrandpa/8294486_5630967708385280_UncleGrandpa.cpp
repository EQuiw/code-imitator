/*input
3
2525 1
2400 5
300 2
120 60
60 90
100 2
80 100
70 10
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
#define N

int S, n;
vector<pair<int, int>> a;

bool check(double speed) {
  for (int i = 0; i < a.size(); i++) {
    double left = S - a[i].fi;
    if (double(S) / speed < left / (double)(a[i].se))
      return false;
  }
  return true;
}

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
    ct++;
    a.clear();
    cin >> S >> n;
    for (int i = 1; i <= n; i++) {
      int x, y;
      cin >> x >> y;
      a.push_back(mp(x, y));
    }
    double l = 0, r = 3e18;
    for (int j = 1; j <= 200; j++) {
      double mid = (l + r) / 2.0;
      if (check(mid))
        l = mid;
      else
        r = mid;
    }
    cout << "Case #" << ct << ": ";
    cout << setprecision(10) << fixed << l << endl;
  }
}