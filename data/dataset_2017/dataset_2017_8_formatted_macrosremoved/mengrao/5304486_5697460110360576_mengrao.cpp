#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <complex>
#include <math.h>
using namespace std;
template <typename T1, typename T2> void Max(T1 &a, T2 b) { a = max(a, (T1)b); }
template <typename T1, typename T2> void Min(T1 &a, T2 b) { a = min(a, (T1)b); }

const int inf = 1e9;
const int N = 50;

vector<pair<int, int>> a[N];
double gram[N];

void solve() {
  int n, p;
  cin >> n >> p;
  for (int i = 0; i < (int)(n); ++i)
    a[i].clear();
  for (int i = 0; i < (int)(n); ++i)
    cin >> gram[i];

  for (int i = 0; i < (int)(n); ++i) {
    double lo = gram[i] * 0.9;
    double hi = gram[i] * 1.1;

    for (int j = 0; j < (int)(p); ++j) {
      double v;
      cin >> v;
      int t1 = floor(v / lo);
      int t2 = ceil(v / hi);
      if (t1 >= t2) {
        // cout << "t2 " << t2 << " t1 " << t1 << endl;
        a[i].push_back(pair<int, int>(t2, t1));
        // cout << a[i].back().ft<<' '<<a[i].back().sd<< endl;
      }
    }
    // rep(j,a[i].size())cout<<a[i][j].ft<<' '<<a[i][j].sd<<''

    sort(a[i].begin(), a[i].end());
    // for (auto e : a[i])cout << e.ft << ' ' << e.sd << ", ";
    // cout << endl;
  }

  vector<int> vec;
  for (auto e : a[0]) {
    for (int i = e.first; i <= (int)(e.second); ++i)
      vec.push_back(i);
    // vec.push_back(e.ft);
    // vec.push_back(e.sd);
  }
  sort(vec.begin(), vec.end());
  int ans = 0;
  for (auto e : vec) {
    bool ok = 1;
    for (int i = 0; i < (int)(n); ++i) {
      bool fd = 0;
      for (auto f : a[i]) {
        if (f.first > e)
          break;
        if (f.first <= e && f.second >= e) {
          fd = 1;
          break;
        }
      }
      if (!fd) {
        ok = 0;
        break;
      }
    }
    if (ok) {
      ans++;
      for (int i = 0; i < (int)(n); ++i) {
        for (auto &f : a[i]) {
          if (f.first <= e && f.second >= e) {
            f.first = f.second = 0;
            break;
          }
        }
      }
    }
  }

  cout << ans << endl;
}

void init() {}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  // freopen("C:\\Users\\LENOVO\\Documents\\Visual Studio
  // 2015\\Projects\\Test\\Input\\in.in", "r", stdin);

  init();
  int T;
  cin >> T;
  for (int TI = 1; TI <= (int)(T); ++TI) {
    cout << "Case #" << TI << ": ";
    // cout << "Case " << TI << ": ";
    solve();
  }

  return 0;
}
