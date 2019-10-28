

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

const int N = int(1111);

int n, k;

inline void gen() { return; }

inline bool read() {
  if (!(cin >> n >> k))
    return false;
  return true;
}

bool used[N];

inline void solve() {
  for (int i = 0; i < int(N); i++)
    used[i] = false;
  used[1] = used[n + 2] = true;
  pt ans;
  for (int kk = 0; kk < int(k); kk++) {
    int bst = -1;
    int minVal = INF;
    int maxVal = -INF;
    int maxLen = -1;
    for (int i = 2; i <= n + 1; i++) {
      if (used[i])
        continue;
      int curL = 0, curR = 0;
      int j = i - 1;
      while (!used[j]) {
        curL++;
        j--;
      }

      j = i + 1;
      while (!used[j]) {
        curR++;
        j++;
      }

      int mn = min(curL, curR);
      int mx = max(curL, curR);
      if (mn > maxLen) {
        // minVal = mn;
        maxVal = mx;
        maxLen = mn;
        bst = i;
      } else if (mn == maxLen && mx > maxVal) {
        maxVal = mx;
        bst = i;
      }
    }

    // cerr << "bst == " << bst << endl;
    used[bst] = true;
    int l = 0, r = 0;
    int j = bst - 1;
    while (!used[j]) {
      j--;
      l++;
    }

    j = bst + 1;
    while (!used[j]) {
      j++;
      r++;
    }

    ans = pt(max(l, r), min(l, r));
  }

  cout << ans.first << ' ' << ans.second << endl;
  return;
}

int main() {
  // assert(false);

  cout << setprecision(10) << fixed;
  cerr << setprecision(10) << fixed;

  srand(int(time(NULL)));

  int T = 1;

  assert(scanf("%d", &T) == 1);

  for (int i = 0; i < int(T); i++) {

    assert(read());
    // read();
    cout << "Case #" << i + 1 << ": ";
    solve();
    // cerr << "curTime == " << clock() << " ms" << endl;
  }

  return 0;
}
