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
const int N = 1000;

void solve() {
  string str;
  int k;
  cin >> str >> k;
  int n = str.size();
  int ans = 0;
  for (int i = 0; i < (int)(n - k + 1); ++i)
    if (str[i] == '-') {
      ans++;
      for (int j = i + 1; j <= (int)(i + k - 1); ++j) {
        if (str[j] == '-')
          str[j] = '+';
        else
          str[j] = '-';
      }
    }
  for (int i = n - k + 1; i <= (int)(n - 1); ++i)
    if (str[i] == '-') {
      cout << "IMPOSSIBLE" << endl;
      return;
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
