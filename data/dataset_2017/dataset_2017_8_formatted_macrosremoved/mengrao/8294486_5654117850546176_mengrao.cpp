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
#include <vector>

#include <math.h>
using namespace std;
template <typename T1, typename T2> void Max(T1 &a, T2 b) { a = max(a, (T1)b); }
template <typename T1, typename T2> void Min(T1 &a, T2 b) { a = min(a, (T1)b); }

const int inf = 1e9;
const int N = 1000;

long long a[6]; // R, O, Y, G, B, V
                // R, B, Y

void solve() {
  long long n;
  cin >> n;
  for (long long i = 0; i < (6); ++i)
    cin >> a[i];
  for (long long i = 0; i < (6); ++i)
    if (a[i] * 2 > n) {
      cout << "IMPOSSIBLE" << endl;
      return;
    }
  int nvar = 0;
  for (long long i = 0; i < (6); ++i)
    nvar += a[i] > 0;
  if (a[1] && a[1] + (nvar > 2) > a[4]) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  if (a[3] && a[3] + (nvar > 2) > a[0]) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  if (a[5] && a[5] + (nvar > 2) > a[2]) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  string ans;
  if (a[1]) {
    for (long long it = 0; it < (a[1]); ++it) {
      ans += "BO";
      a[4]--;
    }
    if (nvar > 2) {
      ans += "B";
      a[4]--;
    }
  }
  if (a[3]) {
    for (long long it = 0; it < (a[3]); ++it) {
      ans += "RG";
      a[0]--;
    }
    if (nvar > 2) {
      ans += "R";
      a[0]--;
    }
  }
  if (a[5]) {
    for (long long it = 0; it < (a[5]); ++it) {
      ans += "YV";
      a[2]--;
    }
    if (nvar > 2) {
      ans += "Y";
      a[2]--;
    }
  }
  a[1] = a[4];
  n = a[0] + a[1] + a[2];
  while (n > 0) {
    char back = ans.empty() ? 'N' : ans.back();
    char front = ans.empty() ? 'N' : ans.front();
    if (back == 'R') {
      if (a[1] > a[2])
        ans += 'B', a[1]--;
      else if (a[2] > a[1])
        ans += 'Y', a[2]--;
      else {
        if (a[1] == 0) {
          cout << "IMPOSSIBLE" << endl;
          return;
        }
        if (front == 'B')
          ans += 'B', a[1]--;
        else
          ans += 'Y', a[2]--;
      }
    }
    if (back == 'B') {
      if (a[0] > a[2])
        ans += 'R', a[0]--;
      else if (a[2] > a[0])
        ans += 'Y', a[2]--;
      else {
        if (a[0] == 0) {
          cout << "IMPOSSIBLE" << endl;
          return;
        }
        if (front == 'R')
          ans += 'R', a[0]--;
        else
          ans += 'Y', a[2]--;
      }
    }
    if (back == 'Y') {
      if (a[0] > a[1])
        ans += 'R', a[0]--;
      else if (a[1] > a[0])
        ans += 'B', a[1]--;
      else {
        if (a[0] == 0) {
          cout << "IMPOSSIBLE" << endl;
          return;
        }
        if (front == 'R')
          ans += 'R', a[0]--;
        else
          ans += 'B', a[1]--;
      }
    }
    if (back == 'N') {
      int best = 0;
      if (a[1] > a[best])
        best = 1;
      if (a[2] > a[best])
        best = 2;
      if (best == 0)
        ans += 'R', a[0]--;
      else if (best == 1)
        ans += 'B', a[1]--;
      else
        ans += 'Y', a[2]--;
    }
    n--;
  }
  if (ans.back() == ans.front()) {
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
  for (long long TI = 1; TI <= (T); ++TI) {
    cout << "Case #" << TI << ": ";
    // cout << "Case " << TI << ": ";
    solve();
  }

  return 0;
}
