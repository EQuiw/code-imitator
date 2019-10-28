#define _CRT_SECURE_NO_WARNINGS

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

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define forn1(i, n) for (int i = 1; i <= int(n); i++)
#define sz(a) int((a).size())
#define all(a) (a).begin(), (a).end()
#define mp make_pair
#define pb push_back
#define x first
#define y second

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld PI = acosl(ld(-1));
const ld EPS = 1e-9;

template <typename T> inline T sqr(const T &x) { return x * x; }

template <typename T> inline T abs(const T &x) { return x > 0 ? x : -x; }

inline bool inside(int x, int y, int n, int m) {
  return x >= 1 && x <= n && y >= 1 && y <= m;
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

li n;

inline void gen() { return; }

inline bool read() {
  if (!(cin >> n))
    return false;
  return true;
}

int a[20], b[20];

inline void solve() {
  forn(i, 20) a[i] = b[i] = 0;
  int len = 0;
  li nn = n;
  while (n) {
    a[len] = n % 10;
    n /= 10;
    len++;
  }

  n = nn;

  reverse(a, a + len);

  for (int i = 0; i < len; i++) {
    int st = (i == 0 ? 0 : b[i - 1]);
    bool found = false;
    for (int d = 9; d >= st; d--) {
      for (int j = i; j < len; j++)
        b[j] = d;
      li val = 0;
      forn(k, len) val = val * 10 + b[k];
      if (val <= n) {
        found = true;
        break;
      } else {
        for (int j = i; j < len; j++)
          b[j] = 0;
      }
    }

    assert(found);
  }

  li ans = 0;
  forn(i, len) ans = ans * 10 + b[i];
  cout << ans << endl;
  return;
}

int main() {
// assert(false);
#ifdef _DEBUG
  assert(freopen("input.txt", "rt", stdin));
  assert(freopen("output.txt", "wt", stdout));
#endif

  cout << setprecision(10) << fixed;
  cerr << setprecision(10) << fixed;

  srand(int(time(NULL)));

  int T = 1;
#define MULTITEST
#ifdef MULTITEST
  assert(scanf("%d", &T) == 1);
#endif

  forn(i, T) {
#ifdef _DEBUG
    cerr << "TEST == " << i << endl;
#endif
    assert(read());
    // read();
    cout << "Case #" << i + 1 << ": ";
    solve();
    // cerr << "curTime == " << clock() << " ms" << endl;
  }

#ifdef _DEBUG
  cerr << "TIME == " << clock() << " ms" << endl;
#endif
  return 0;
}