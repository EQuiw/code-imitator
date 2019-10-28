

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

string s;
int k;

inline void gen() { return; }

inline bool read() {
  if (!(cin >> s >> k))
    return false;
  return true;
}

inline void solve() {
  int n = int((s).size());
  int ans = 0;
  for (int i = 0; i + k - 1 < n; i++) {
    if (s[i] == '+')
      continue;
    ans++;
    for (int j = i; j <= i + k - 1; j++) {
      if (s[j] == '+')
        s[j] = '-';
      else
        s[j] = '+';
    }
  }

  bool ok = true;
  for (int i = 0; i < int(n); i++)
    if (s[i] == '-')
      ok = false;
  if (ok)
    cout << ans << endl;
  else
    cout << "IMPOSSIBLE" << endl;
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
