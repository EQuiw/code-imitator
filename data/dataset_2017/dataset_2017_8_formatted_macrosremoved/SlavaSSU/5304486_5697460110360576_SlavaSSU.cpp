

#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

//#include <cstdint>
//#include <cstdlib>
#include <cassert>
//#include <cctype>
#include <algorithm>
#include <climits>
#include <cmath>
#include <ctime>
#include <functional>
#include <numeric>

#include <array>
#include <bitset>
#include <cstring>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld PI = acosl(ld(-1));
const ld EPS = 1e-9;

template <typename T> inline T sqr(const T &first) { return first * first; }

template <typename T> inline T abs(const T &first) {
  return first > 0 ? first : -first;
}

inline bool inside(int first, int second, int n, int m) {
  return first >= 1 && first <= n && second >= 1 && second <= m;
}

inline int rnd() { return abs(rand() ^ (rand() << 15)); }

inline int rnd(int n) {
  assert(n > 0);
  return rnd() % n;
}

inline int rnd(int lf, int rg) { return lf + rnd(rg - lf + 1); }

inline li rndLL() { return rnd() * 1LL * rnd() + rnd(); }

const int dx[4] = {-1, 0, +1, 0};
const int dy[4] = {0, +1, 0, -1};

const int dx8[8] = {-1, -1, 0, +1, +1, +1, 0, -1};
const int dy8[8] = {0, +1, +1, +1, 0, -1, -1, -1};

const int N = int(33);

int n, m, a[N], b[N][N];

inline void gen() { return; }

inline bool read() {
  if (!(cin >> n >> m))
    return false;
  for (int i = 0; i < int(n); i++)
    (cin >> a[i]);
  for (int i = 0; i < int(n); i++) {
    for (int j = 0; j < int(m); j++)
      (cin >> b[i][j]);
  }
  return true;
}

bool used[N][N];
int ans = 0;

inline bool can(const vector<int> &v) {
  // cerr << "v to check == " << endl;
  // for (int x : v) cerr << x << ' '; cerr << endl;
  for (int cnt = 1; cnt <= 1111111; cnt++) {
    bool ok = true;
    // cerr << "cnt == " << cnt << endl;
    for (int i = 0; i < int(n); i++) {
      //	cerr << "ing == " << i << endl;
      li need = a[i] * 1LL * cnt;
      li lf = need * 90;
      if (lf % 100 == 0)
        lf /= 100;
      else
        lf = lf / 100 + 1;
      li rg = need * 110;
      rg /= 100;
      li cur = v[i];
      // cerr << "lf rg cur == " << lf << ' ' << rg << ' ' << cur << endl;
      if (!(lf <= cur && cur <= rg)) {
        ok = false;
        // break;
      }
    }

    if (ok)
      return true;
    // if (cnt > 5) break;
  }

  // cerr << "wtf == " << endl;
  return false;
}

void brute(int cnt, int i, int cur, vector<int> v) {
  // cerr << "cnt i cur == " << cnt << ' ' << i << ' ' << cur << endl;
  if (cnt == m) {
    ans = max(ans, cur);
    return;
  }

  if (i == n) {
    cur += can(v);
    brute(cnt + 1, 0, cur, {});
    return;
  }

  for (int j = 0; j < int(m); j++)
    if (!used[i][j]) {
      used[i][j] = true;
      v.push_back(b[i][j]);
      brute(cnt, i + 1, cur, v);
      v.pop_back();
      used[i][j] = false;
    }
}

bool good[N][N];

inline void solve() {
  for (int i = 0; i < int(N); i++)
    for (int j = 0; j < int(N); j++)
      good[i][j] = used[i][j] = false;
  ans = 0;
  // brute(0, 0, 0, {});
  if (n == 1) {
    for (int j = 0; j < int(m); j++)
      ans += can(vector<int>(1, b[0][j]));
  } else if (n == 2) {
    for (int i = 0; i < int(m); i++)
      for (int j = 0; j < int(m); j++)
        good[i][j] = can({b[0][i], b[1][j]});
    vector<vector<int>> dp((1 << m), vector<int>((1 << m), -1));
    dp[0][0] = 0;
    for (int mask1 = 0; mask1 < int((1 << m)); mask1++)
      for (int mask2 = 0; mask2 < int((1 << m)); mask2++) {
        int cur = dp[mask1][mask2];
        if (cur < 0)
          continue;
        for (int i = 0; i < int(m); i++) {
          if (mask1 & (1 << i))
            continue;
          for (int j = 0; j < int(m); j++) {
            if (mask2 & (1 << j))
              continue;
            dp[mask1 | (1 << i)][mask2 | (1 << j)] =
                max(dp[mask1 | (1 << i)][mask2 | (1 << j)], cur + good[i][j]);
          }
        }
      }

    for (int mask1 = 0; mask1 < int((1 << m)); mask1++)
      for (int mask2 = 0; mask2 < int((1 << m)); mask2++)
        ans = max(ans, dp[mask1][mask2]);
  } else
    cerr << "bad test" << endl;
  cout << ans << endl;
  return;
}

int main() {
  // assert(false);
  //#ifdef _DEBUG
  (freopen("input.txt", "rt", stdin));
  (freopen("output.txt", "wt", stdout));
  //#endif

  cout << setprecision(10) << fixed;
  cerr << setprecision(10) << fixed;

  srand(int(time(NULL)));

  int T = 1;

  (scanf("%d", &T) == 1);

  for (int i = 0; i < int(T); i++) {
    //#ifdef _DEBUG
    cerr << "TEST == " << i << endl;
    //#endif
    (read());
    // read();
    cout << "Case #" << i + 1 << ": ";
    solve();
    // cerr << "curTime == " << clock() << " ms" << endl;
  }

  return 0;
}
