#if 1
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;

const LD eps = 1e-9;
const LD pi = acos(-1.0);
const LL inf = 1e+9;

#define mp make_pair
#define pb push_back
#define X first
#define Y second

#define dbg(x)                                                                 \
  { cerr << #x << " = " << x << endl; }

// extended template
#pragma comment(linker, "/STACK:36777216")
typedef vector<int> vi;
typedef vector<vi> vvi;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

template <typename T> istream &operator>>(istream &, vector<T> &);
template <typename T> ostream &operator<<(ostream &, const vector<T> &);

#define START clock_t _clock = clock();
#define END                                                                    \
  cerr << endl << "time: " << (clock() - _clock) / LD(CLOCKS_PER_SEC) << endl;

#define NAME "angle2"

void solve() {
  int t;
  cin >> t;
  for (int q = 0; q < t; q++) {
    string s;
    int k;
    cin >> s >> k;
    int n = s.size();
    vector<int> add(n);

    int ans = 0;
    int sum = 0;
    for (int i = 0; i < n - k + 1; i++) {
      int val = s[i] == '-' ? 0 : 1;
      sum += add[i];
      val += sum;

      if (val % 2 == 0) {
        ans++;
        add[i] += 1;
        sum += 1;
        if (i + k < n)
          add[i + k] += 1;
      }
    }

    bool fl = 1;
    for (int i = n - k + 1; i < n; i++) {
      int val = s[i] == '-' ? 0 : 1;
      sum += add[i];
      val += sum;

      if (val % 2 == 0)
        fl = 0;
    }

    cout << "Case #" << q + 1 << ": ";
    if (fl == 0)
      cout << "IMPOSSIBLE" << endl;
    else
      cout << ans << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  // START
  // freopen(NAME ".in", "r", stdin); freopen(NAME ".out", "w", stdout);
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);
  solve();

  // END
  return 0;
}
/*******************************************
*******************************************/

template <typename T> istream &operator>>(istream &is, vector<T> &v) {
  forn(i, v.size()) is >> v[i];
  return is;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
  forn(i, v.size()) os << v[i] << " ";
  return os;
}
#endif
