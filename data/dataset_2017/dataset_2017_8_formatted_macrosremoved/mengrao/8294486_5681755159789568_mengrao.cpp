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

const double inf = 1e11;
const int N = 100;

double d[N][N];
double e[N], s[N];
double memo[N][N];
double dsum[N];
long long n;

double go(int i, int horse) {
  double &ret = memo[i][horse];
  if (ret > 0)
    return ret;
  if (i == n - 1)
    return 0;
  ret = inf;
  double horse_dis = dsum[i + 1] - dsum[horse];
  if (e[horse] >= horse_dis) {
    Min(ret, d[i][i + 1] / s[horse] + go(i + 1, horse));
  }
  if (e[i] >= d[i][i + 1]) {
    Min(ret, d[i][i + 1] / s[i] + go(i + 1, i));
  }
  if (ret < inf) {
    // cout << "ok " << i << " " << horse <<" "<<ret<< endl;
  }
  return ret;
}

void solve() {
  long long q;
  cin >> n >> q;
  for (long long i = 0; i < (n); ++i)
    cin >> e[i] >> s[i];
  for (long long i = 0; i < (n); ++i)
    for (long long j = 0; j < (n); ++j)
      cin >> d[i][j];
  dsum[0] = 0;
  for (long long i = 1; i <= (n - 1); ++i)
    dsum[i] = dsum[i - 1] + d[i - 1][i];
  while (q--) {
    long long u, v;
    cin >> u >> v;
    memset(memo, 0, sizeof(memo));
    double ans = go(0, 0);
    cout << setprecision(8) << ans << endl;

    for (long long i = 0; i < (n - 1); ++i) {
      bool fd = 0;
      for (long long j = 0; j < (n); ++j)
        if (memo[i][j] > 0 && memo[i][j] < inf) {
          fd = 1;
          break;
        }
      if (!fd) {
        cout << "bad " << i << endl;
      }
    }
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
  for (long long TI = 1; TI <= (T); ++TI) {
    cout << "Case #" << TI << ": ";
    // cout << "Case " << TI << ": ";
    solve();
  }

  return 0;
}
