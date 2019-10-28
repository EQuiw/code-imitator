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

bool check(string &s) {
  int n = s.size();
  int pos = -1;
  for (int i = 0; i < n - 1; i++) {
    if (s[i] > s[i + 1]) {
      pos = i;
      break;
    }
  }

  if (pos == -1)
    return true;

  s[pos]--;
  for (int i = pos + 1; i < n; i++)
    s[i] = '9';

  int p = s.find_first_not_of("0");
  if (p != string::npos)
    s = s.substr(p);
  return false;
}

void solve() {
  int t;
  cin >> t;
  for (int q = 0; q < t; q++) {
    string s;
    cin >> s;
    while (!check(s)) {
    }
    cout << "Case #" << q + 1 << ": " << s << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  // START
  // freopen(NAME ".in", "r", stdin); freopen(NAME ".out", "w", stdout);
  freopen("B-small-attempt0.in", "r", stdin);
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
