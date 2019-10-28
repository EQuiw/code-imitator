/*input
6
2 1
500 300
900
660
2 1
500 300
1500
809
2 2
50 100
450 449
1100 1101
2 1
500 300
300
500
1 8
10
11 13 17 11 16 14 12 18
3 3
70 80 90
1260 1500 700
800 1440 1600
1700 1620 900
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
#define N 55

int n, p;
vector<vector<int>> a(N);
int need[N];

int find_base(int x, int y) {
  int l = 1, r = 1e9;
  while (l != r) {
    int mid = (l + r) / 2;
    if (y * 100 <= x * mid * 110) {
      r = mid;
    } else
      l = mid + 1;
  }
  if (y * 100 > x * l * 110)
    return -1;
  return l;
}

bool valid(int x, int y, int num) {
  if (x * num * 90 <= y * 100 && y * 100 <= x * num * 110)
    return true;
  return false;
}

bool check(int num) {
  for (int i = 2; i <= n; i++) {
    bool ok = false;
    while (!a[i].empty()) {
      if (a[i].back() * 100 < num * need[i] * 90)
        a[i].pop_back();
      else if (valid(need[i], a[i].back(), num)) {
        ok = true;
        a[i].pop_back();
        break;
      } else {
        return false;
      }
    }
    if (!ok)
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
    cin >> n >> p;
    a.assign(55, vector<int>());
    for (int i = 1; i <= n; i++)
      cin >> need[i];
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= p; j++) {
        int t;
        cin >> t;
        a[i].push_back(t);
      }
      sort(a[i].begin(), a[i].end(), greater<int>());
    }
    int ans = 0;
    for (int i = (int)a[1].size() - 1; i >= 0; i--) {
      int base = find_base(need[1], a[1][i]);
      if (base == -1) {
        a[1].pop_back();
        continue;
      }
      for (int j = base;; j++) {
        if (a[1][i] * 100 < need[1] * j * 90)
          break;
        if (check(j)) {
          ans++;
          break;
        }
      }
    }
    cout << "Case #" << ct << ": " << ans << endl;
  }
}