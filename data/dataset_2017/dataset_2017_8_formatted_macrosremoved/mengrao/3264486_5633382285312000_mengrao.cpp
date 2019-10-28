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

long long ndig(int n) {
  long long ret = 1;
  while (--n) {
    ret *= 10;
  }
  return ret;
}

void solve() {
  long long n;
  cin >> n;
  long long t = n;
  int dig = 0;
  int last = -1;
  int lastd = 9;
  while (t) {
    dig++;
    int cur = t % 10;
    t /= 10;
    if (cur > lastd)
      last = -2;
    if (cur < lastd && last == -2) {
      last = dig;
    }
    lastd = cur;
  }
  if (last != -1) {
    if (last == -2)
      last = dig;
    else
      last--;
    long long t = ndig(last);
    n -= n % t;
    n--;
  }
  cout << n << endl;
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
