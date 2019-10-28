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

int n, D;
pt a[N];

inline void gen() { return; }

inline bool read() {
  if (!(cin >> D >> n))
    return false;
  forn(i, n) assert(scanf("%d %d", &a[i].x, &a[i].y) == 2);
  return true;
}

ld t[N];

inline void solve() {
  sort(a, a + n);
  t[n - 1] = ld(D - a[n - 1].x) / a[n - 1].y;
  for (int i = n - 2; i >= 0; i--) {
    ld cur = ld(D - a[i].x) / a[i].y;
    t[i] = max(cur, t[i + 1]);
  }

  /*
  v * t == D
  v == D / t
  */
  ld ans = ld(D) / t[0];
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
    cerr << "curTime == " << clock() << " ms" << endl;
  }

#ifdef _DEBUG
  cerr << "TIME == " << clock() << " ms" << endl;
#endif
  return 0;
}