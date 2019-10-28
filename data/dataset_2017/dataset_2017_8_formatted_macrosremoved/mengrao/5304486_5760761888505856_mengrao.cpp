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
const int N = 25;

char a[N][N];
bool mk[N][N];

void solve() {
  int r, c;
  cin >> r >> c;
  for (int i = 0; i < (int)(r); ++i)
    for (int j = 0; j < (int)(c); ++j)
      cin >> a[i][j];
  for (int i = 0; i < (int)(r); ++i)
    for (int j = 0; j < (int)(c); ++j)
      mk[i][j] = 0;
  for (int i = 0; i < (int)(r); ++i)
    for (int j = 0; j < (int)(c); ++j)
      if (a[i][j] != '?' && !mk[i][j]) {
        char ch = a[i][j];
        int ci = j - 1;
        while (ci >= 0 && a[i][ci] == '?')
          mk[i][ci] = 1, a[i][ci--] = ch;
        ci++;
        int cj = j + 1;
        while (cj < c && a[i][cj] == '?')
          mk[i][cj] = 1, a[i][cj++] = ch;
        cj--;
        int ri = i - 1;
        while (ri >= 0) {
          bool ok = 1;
          for (int jj = ci; jj <= (int)(cj); ++jj)
            if (a[ri][jj] != '?') {
              ok = 0;
              break;
            }
          if (!ok)
            break;
          for (int jj = ci; jj <= (int)(cj); ++jj)
            a[ri][jj] = ch, mk[ri][jj] = 1;
          ri--;
        }
        ri = i + 1;
        while (ri < r) {
          bool ok = 1;
          for (int jj = ci; jj <= (int)(cj); ++jj)
            if (a[ri][jj] != '?') {
              ok = 0;
              break;
            }
          if (!ok)
            break;
          for (int jj = ci; jj <= (int)(cj); ++jj)
            a[ri][jj] = ch, mk[ri][jj] = 1;
          ri++;
        }
      }
  cout << endl;
  for (int i = 0; i < (int)(r); ++i) {
    for (int j = 0; j < (int)(c); ++j)
      cout << a[i][j];
    cout << endl;
  }
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
