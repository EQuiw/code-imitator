/*input
1
4 6 0 3 0 4 0
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

int a[10];
int n;
deque<int> order;
bool ok = true;
void solveez(int u, int v, bool side = 0, bool locked = 0) {
  if (locked) {
    if (a[u] != a[v]) {
      ok = false;
      return;
    }
  } else {
    if (abs(a[u] - a[v]) > 1) {
      ok = false;
      return;
    }
  }
  if (side == 1) {
    while (a[u] > 0 && a[v] > 0) {
      order.push_front(u);
      order.push_front(v);
      a[u]--;
      a[v]--;
    }
    if (a[u])
      order.push_front(u);
    else if (a[v])
      order.push_front(v);
  } else {
    while (a[u] > 0 && a[v] > 0) {
      order.push_back(u);
      order.push_back(v);
      a[u]--;
      a[v]--;
    }
    if (a[u])
      order.push_back(u);
    else if (a[v])
      order.push_back(v);
  }
}

void recreate(int x, int y, int z, int need) {
  order.clear();
  while (need--) {
    order.push_back(x);
    order.push_back(y);
    order.push_back(z);
  }
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  // #ifdef UncleGrandpa
  // 	freopen("1test.inp", "r", stdin);
  // 	freopen("1test.out", "w", stdout);
  // #endif
  int T;
  cin >> T;
  int ct = 0;
  while (T--) {
    order.clear();
    ok = true;
    ct++;
    cin >> n;
    for (int i = 1; i <= 6; i++)
      cin >> a[i];
    int done = min(a[1], min(a[3], a[5]));
    a[1] -= done;
    a[3] -= done;
    a[5] -= done;
    recreate(1, 3, 5, done);
    // cout << a[1] << sp << a[3] << sp << a[5] << endl;
    if (order.empty()) {
      if (a[1] == 0)
        solveez(3, 5, 0, 1);
      else if (a[3] == 0)
        solveez(5, 1, 0, 1);
      else
        solveez(1, 3, 0, 1);
    } else {
      if (a[1] + a[3] + a[5] == 0) {

      } else if (a[1] + a[3] == 0) {
        if (a[5] > 1)
          ok = false;
        else {
          recreate(1, 5, 3, done);
          order.push_back(5);
        }
      } else if (a[1] + a[5] == 0) {
        if (a[3] > 1)
          ok = false;
        else
          order.push_back(3);
      } else if (a[3] + a[5] == 0) {
        if (a[1] > 1)
          ok = false;
        else {
          recreate(3, 1, 5, done);
          order.push_back(1);
        }
      } else if (a[1] == 0) {
        if (abs(a[5] - a[3]) > 1) {
          ok = false;
        } else if (a[5] >= a[3]) {
          recreate(1, 5, 3, done);
          solveez(5, 3);
        } else if (a[3] > a[5]) {
          solveez(3, 5);
        }
      } else if (a[3] == 0) {
        if (abs(a[5] - a[1]) > 1) {
          ok = false;
        } else if (a[5] >= a[1]) {
          recreate(3, 5, 1, done);
          solveez(5, 1);
        } else if (a[1] > a[5]) {
          recreate(3, 1, 5, done);
          solveez(1, 5);
        }
      } else if (a[5] == 0) {
        if (abs(a[3] - a[1]) > 1) {
          ok = false;
        } else if (a[3] >= a[1]) {
          recreate(5, 3, 1, done);
          solveez(3, 1);
        } else if (a[1] > a[3]) {
          recreate(5, 1, 3, done);
          solveez(1, 3);
        }
      }
    }
    cout << "Case #" << ct << ": ";
    if (!ok)
      cout << "IMPOSSIBLE" << endl;
    else {
      for (int i = 0; i < order.size() - 1; i++) {
        assert(order[i] != order[i + 1]);
      }
      assert(order.back() != order.front());
      for (auto it : order) {
        if (it == 1)
          cout << 'R';
        else if (it == 3)
          cout << 'Y';
        else if (it == 5)
          cout << 'B';
      }
      cout << endl;
    }
  }
}