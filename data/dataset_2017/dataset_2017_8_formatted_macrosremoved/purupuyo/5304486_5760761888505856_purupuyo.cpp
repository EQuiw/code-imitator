#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#include <unordered_map>
#include <unordered_set>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int INF = 1 << 30;
const double EPS = 1e-10;

double zero(double d) { return abs(d) < EPS ? 0.0 : d; }

template <class T> bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T> bool chmin(T &a, const T &b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
  return os << '(' << p.first << ',' << p.second << ')';
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  os << '[';
  for (int i = 0; i < (int)(a.size()); i++)
    os << (i ? " " : "") << a[i];
  return os << ']';
}

string toString(int i) {
  stringstream ss;
  ss << i;
  return ss.str();
}

const int MOD = 1000000007;

// a^k
ll fpow(ll a, ll k, int M) {
  ll res = 1ll;
  ll x = a;
  while (k != 0) {
    if ((k & 1) == 1)
      res = (res * x) % M;
    x = (x * x) % M;
    k >>= 1;
  }
  return res;
}

struct prepare {
  prepare() {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(8);
    ios_base::sync_with_stdio(false);
  }
} _prepare;

void solve() {
  int R, C;
  cin >> R >> C;

  vector<string> field(R);
  //    vector<pii> start;
  map<int, pii> sized;
  map<int, pii> pos;

  for (int i = 0; i < (int)(R); i++)
    cin >> field[i];

  for (int i = 0; i < (int)(R); i++) {
    for (int j = 0; j < (int)(C); j++) {
      if (field[i][j] != '?') {
        int code = field[i][j] - 'A';
        pos[code] = make_pair(i, j);
      }
    }
  }

  for (int r = 0; r < (int)(R); r++) {
    for (int c = 1; c < (int)(C); c++) {
      if (field[r][c] == '?')
        field[r][c] = field[r][c - 1];
    }
    for (int c = C - 2; c >= 0; c--) {
      if (field[r][c] == '?')
        field[r][c] = field[r][c + 1];
    }
  }

  for (int c = 0; c < (int)(C); c++) {
    for (int r = 1; r < (int)(R); r++) {
      if (field[r][c] == '?')
        field[r][c] = field[r - 1][c];
    }
    for (int r = R - 2; r >= 0; r--) {
      if (field[r][c] == '?')
        field[r][c] = field[r + 1][c];
    }
  }

  for (int r = 0; r < (int)(R); r++) {
    cout << field[r] << endl;
  }
}

int main() {
  int T;
  cin >> T;
  for (int _t = 0; _t < (int)(T); _t++) {
    cout << "Case #" << (_t + 1) << ":" << endl;
    solve();
  }
  return 0;
}
