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

vector<int> need;
int n, p;

bool checkProportion(LL f, LL d) {
  return (9 * d <= 10 * f && 10 * f <= 11 * d);
}

bool check(int v1, int v2) {
  int cnt = (10 * v1) / (11 * need[0]);
  // cnt = v1 / need[0];
  for (int i = max(1, (10 * v1) / (11 * need[0]) - 15);
       i <= (10 * v1) / (9 * need[0]) + 15; i++) {

    LL f = v1;
    LL d = LL(i) * need[0];
    if (checkProportion(f, d)) {
      LL f2 = v2;
      LL d2 = need[1] * i;
      if (checkProportion(f2, d2))
        return true;
    }
  }
  return false;
}
void solve() {
  int t;
  cin >> t;
  for (int w = 0; w < t; w++) {
    int n, p;
    cerr << w << endl;
    cin >> n >> p;
    need.assign(n, 0);
    for (int i = 0; i < n; i++)
      cin >> need[i];

    vector<vector<int>> a(n, vector<int>(p));
    vector<int> perm(p);

    for (int i = 0; i < n; i++) {
      for (int k = 0; k < p; k++) {
        cin >> a[i][k];
        perm[k] = k;
      }
    }
    if (n == 1) {
      need.pb(0);
      a.pb(vector<int>(p, 0));
      n++;
    }
    int ans = 0;
    do {
      int cur = 0;
      for (int i = 0; i < p; i++) {
        cur += check(a[0][perm[i]], a[1][i]);
      }
      ans = max(cur, ans);
    } while (next_permutation(all(perm)));

    cout << "Case #" << w + 1 << ": " << ans << endl;
  }
}

int main() {

  // START
  // freopen(NAME ".in", "r", stdin); freopen(NAME ".out", "w", stdout);
  freopen("B-small-attempt1.in", "r", stdin);
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