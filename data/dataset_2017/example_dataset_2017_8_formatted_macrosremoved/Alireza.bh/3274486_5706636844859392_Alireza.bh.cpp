
#pragma comment(linker, "/STACK:100000000000")
#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
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

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;

int a[1500];
int memo[1500][1500][3][3];
int inf = 1 << 30;
int f(int curMin, int cameronTime, int currentParent, int startedParent) {
  if (curMin == 60 * 24) {
    if (cameronTime != 60 * 12)
      return inf;
    if (startedParent != currentParent)
      return 1;
    return 0;
  }

  int res = inf;
  int &ret = memo[curMin][cameronTime][currentParent][startedParent];
  if (ret != -1)
    return ret;
  if (a[curMin] == currentParent) {
    int newCurrentParent = (currentParent == 1) ? 2 : 1;
    int newCameronTime = newCurrentParent == 1 ? cameronTime + 1 : cameronTime;
    res = min(res, 1 + f(curMin + 1, newCameronTime, newCurrentParent,
                         startedParent));
  } else {
    int newCameronTime = currentParent == 1 ? cameronTime + 1 : cameronTime;
    res = min(res, f(curMin + 1, newCameronTime, currentParent, startedParent));
    if (a[curMin] == 0) {
      int newCurrentParent = (currentParent == 1) ? 2 : 1;
      int newCameronTime =
          newCurrentParent == 1 ? cameronTime + 1 : cameronTime;
      res = min(res, 1 + f(curMin + 1, newCameronTime, newCurrentParent,
                           startedParent));
    }
  }
  return ret = res;
}
int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  int Tcase;
  cin >> Tcase;
  for (int(cas) = 0; (cas) < (Tcase); (cas)++) {
    printf("Case #%d: ", cas + 1);
    int Ac, Aj;
    cin >> Ac >> Aj;
    memset((a), (0), sizeof(a));
    for (int(i) = 0; (i) < (Ac); (i)++) {
      int st, en;
      cin >> st >> en;
      for (int(j) = (st); (j) < (en); (j)++)
        a[j] = 1;
    }
    for (int(i) = 0; (i) < (Aj); (i)++) {
      int st, en;
      cin >> st >> en;
      for (int(j) = (st); (j) < (en); (j)++)
        a[j] = 2;
    }
    memset((memo), (-1), sizeof(memo));
    cout << min(f(0, 0, 1, 1), f(0, 0, 2, 2)) << endl;
  }
}
