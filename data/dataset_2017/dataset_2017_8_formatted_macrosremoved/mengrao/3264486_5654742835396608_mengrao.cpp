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

pair<long long, long long> f[2][2];

void solve() {
  long long n, k;
  cin >> n >> k;
  int c = 0;
  f[0][0].first = n;
  f[0][0].second = 1;
  f[0][1].first = f[0][1].second = 0;
  while (1) {
    if (f[c][0].second + f[c][1].second >= k) {
      long long t = f[c][0].second >= k ? f[c][0].first : f[c][1].first;
      t--;
      long long ans1 = (t + 1) / 2;
      long long ans2 = t / 2;
      cout << ans1 << ' ' << ans2 << endl;
      break;
    }
    k -= f[c][0].second + f[c][1].second;
    memset(f[!c], 0, sizeof(f[!c]));
    long long t1 = f[c][0].first - 1;
    long long t2 = (t1 + 1) / 2;
    long long t3 = t1 / 2;
    f[!c][0] = pair<long long, long long>(t2, f[c][0].second);
    if (t3 == t2) {
      f[!c][0].second *= 2;
    } else
      f[!c][1] = pair<long long, long long>(t3, f[c][0].second);
    if (f[c][1].second) {
      t1 = f[c][1].first - 1;
      t2 = (t1 + 1) / 2;
      t3 = t1 / 2;
      if (t2 == t3) {
        f[!c][1].second += 2 * f[c][1].second;
      } else {
        f[!c][0].second += f[c][1].second;
        f[!c][1] = pair<long long, long long>(t3, f[c][1].second);
      }
    }
    c = !c;
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
