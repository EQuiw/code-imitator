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

pii range(int target) {
  int from = ceil((double)target * 0.9);
  int to = floor((double)target * 1.1);
  return make_pair(from, to);
}

bool between(int now, int target) {
  pii t = range(target);
  //    cout <<  "   bt: " << t << now << endl;
  return t.first <= now && now <= t.second;
}

pii conv(int now) {
  int e = floor((double)now / 0.9);
  int s = ceil((double)now / 1.1);
  return make_pair(s, e);
}

pii check(int now, int target) {
  //    cout << "  chk: " << now << " " << target << endl;
  pii ran = range(target);
  int am1 = ran.first / now - 1;
  int am2 = ran.second / now + 1;
  pii ans = make_pair(INF, -1);
  //    cout << "  chk2: " << am1 << " " << am2 << endl;
  for (int i = max(1, am1); i < (int)(am2 + 1); i++) {
    if (between(target, now * i)) {
      chmin(ans.first, i);
      chmax(ans.second, i);
    }
  }
  return ans;
}

void solve() {
  int N, P;
  cin >> N >> P;

  vi R(N);
  for (int i = 0; i < (int)(N); i++)
    cin >> R[i];

  vvi Q(N, vi(P));
  for (int i = 0; i < (int)(N); i++) {
    for (int j = 0; j < (int)(P); j++) {
      cin >> Q[i][j];
    }
  }

  for (int i = 0; i < (int)(N); i++) {
    sort(((Q[i]).begin()), ((Q[i]).end()));
  }

  vector<vector<pii>> need(N, vector<pii>(P));
  for (int i = 0; i < (int)(N); i++) {
    for (int j = 0; j < (int)(P); j++) {
      need[i][j] = conv(Q[i][j]);
    }
  }

  int ans = 0;
  if (N <= 2) {
    for (int pack = 0; pack < (int)(P); pack++) {
      int from = ceil((double)need[0][pack].first / R[0]);
      int to = floor((double)need[0][pack].second / R[0]);

      bool gok = false;
      for (int i = from; i < (int)(to + 1); i++) {
        bool ok = (need[0][pack].first <= R[0] * i &&
                   R[0] * i <= need[0][pack].second);
        //                cout << " fc: " << need[0][pack].first << " " <<
        //                R[0]*i << " & "<<  R[0]*i << " " <<
        //                need[0][pack].second << endl;

        if (!ok)
          continue;

        ok = (N == 1);

        for (int g = 1; g < (int)(N); g++) {
          for (int p = 0; p < (int)(P); p++) {
            if (need[g][p].first <= R[g] * i && R[g] * i <= need[g][p].second) {
              //                            cout << need[g][p].first << " " <<
              //                            R[g]*i << " & "<<  R[g]*i << " " <<
              //                            need[g][p].second << endl;
              ok = true;
              need[g][p] = make_pair(-1, -1);
              break;
            }
          }
        }

        gok |= ok;

        if (ok)
          break;
      }

      if (gok) {
        ans++;
      }
    }

    cout << ans;
  } else {
    cout << "IMP";
  }
}

int main() {
  int T;
  cin >> T;
  for (int _t = 0; _t < (int)(T); _t++) {
    cout << "Case #" << (_t + 1) << ": ";
    solve();
    cout << endl;
  }
  return 0;
}
