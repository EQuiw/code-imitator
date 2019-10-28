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

const int N = int(33);

int n, m;
char a[N][N];

inline void gen() {
  n = 25, m = 25;
  vector<char> v;
  for (char c = 'A'; c <= 'Z'; c++)
    v.push_back(c);
  random_shuffle(all(v));
  forn1(i, n) forn1(j, m) {
    if ((rnd() % 3 == 2) && !v.empty()) {
      a[i][j] = v.back();
      v.pop_back();
    } else
      a[i][j] = '?';
  }
  return;
}

inline bool read() {
  // gen(); return true;
  if (!(cin >> n >> m))
    return false;
  forn1(i, n) forn1(j, m) assert(cin >> a[i][j]);
  return true;
}

bool used[N][N];

inline void solve() {
  forn(i, N) forn(j, N) used[i][j] = false;
  forn1(ii, n) forn1(jj, m) {
    if (used[ii][jj])
      continue;
    if (a[ii][jj] == '?')
      continue;
    // cerr << "ii jj == " << ii << ' ' << jj << endl;
    int j1 = jj - 1;
    while (j1 >= 1 && a[ii][j1] == '?')
      j1--;
    int j2 = jj + 1;
    while (j2 <= m && a[ii][j2] == '?')
      j2++;
    j1++, j2--;
    //	cerr << "j1 j2 == " << j1 << ' ' << j2 << endl;
    int i1 = ii;
    bool ok = true;
    while (ok) {
      if (i1 == 0) {
        ok = false;
        break;
      }

      for (int j = j1; j <= j2; j++)
        if (a[i1][j] != '?' && a[i1][j] != a[ii][jj]) {
          ok = false;
          break;
        }

      if (!ok)
        break;
      i1--;
    }

    i1++;
    int i2 = ii;
    ok = true;
    while (ok) {
      //	cerr << "tocheck == " << i2 << endl;
      if (i2 == n + 1) {
        ok = false;
        break;
      }

      for (int j = j1; j <= j2; j++) {
        //	cerr << " sym tocheck == " << a[i2][j] << endl;
        if (a[i2][j] != '?' && a[i2][j] != a[ii][jj]) {
          ok = false;
          break;
        }
      }

      if (!ok)
        break;
      // cerr << "i2 is good == " << i2 << endl;
      i2++;
    }

    i2--;

    // cerr << "i1 i2 == " << i1 << ' ' << i2 << endl;
    // cerr << "ii jj i1 i2 j1 j2 == " << ii << ' ' << jj << ' ' << i1 << ' ' <<
    // i2 << ' ' << j1 << ' ' << j2 << endl;
    for (int i = i1; i <= i2; i++)
      for (int j = j1; j <= j2; j++) {
        used[i][j] = true;
        a[i][j] = a[ii][jj];
      }

    /*
    cerr << "curtab == " << endl;
    forn1(iii, n) {
            forn1(jjj, m) cerr << a[iii][jjj];
            cerr << endl;
    }
    */
  }

  forn1(i, n) forn1(j, m) assert(used[i][j]);
  cout << endl;
  forn1(i, n) {
    forn1(j, m) cout << a[i][j];
    cout << endl;
  }
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