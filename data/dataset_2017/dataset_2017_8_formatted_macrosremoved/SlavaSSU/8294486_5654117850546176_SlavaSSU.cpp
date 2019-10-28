

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

const int N = int(2e5) + 555;

int n;
const string types = "ROYGBV";
int a[6];

inline void gen() { return; }

inline bool read() {
  if (!(cin >> n))
    return false;
  for (int i = 0; i < int(6); i++)
    assert(cin >> a[i]);
  return true;
}

inline int lf(int pos) {
  pos--;
  if (pos < 0)
    pos = n - 1;
  return pos;
}

inline int rg(int pos) {
  pos++;
  if (pos == n)
    pos = 0;
  return pos;
}

inline void solve() {
  string ans(n, '.');
  int lst = 0;
  while (1) {
    int mx = 0;
    for (int i = 0; i < int(6); i++)
      if (a[i] > a[mx])
        mx = i;
    char c = types[mx];
    int pos = mx;
    mx = a[mx];
    a[pos] = 0;
    if (mx == 0)
      break;
    // int tries = 0;
    // cerr << "pos mx c == " << pos << ' ' << mx << ' ' << c << endl;
    for (int kk = 0; kk < int(mx); kk++) {
      bool has = false;
      int tries = 0;
      while (ans[lst] != '.' || ans[lf(lst)] == c || ans[rg(lst)] == c) {
        tries++;
        lst = rg(lst);
        if (tries > 10 * n)
          break;
      }

      if (tries > 10 * n) {
        puts("IMPOSSIBLE");
        return;
      }

      // cerr << "set to pos == " << lst << endl;
      ans[lst] = c;
    }
  }

  cout << ans << endl;
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
    cerr << "curTime == " << clock() << " ms" << endl;
  }

  return 0;
}
