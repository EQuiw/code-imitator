#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

#define EPS 1e-12
#define ull unsigned long long
#define ll long long
#define VI vector<ll>
#define PII pair<ll, ll>
#define VVI vector<vector<ll>>
#define REP(i, n) for (int i = 0, _n = (n); (i) < (int)_n; ++i)
#define RANGE(i, a, b) for (int i = (int)a, _b = (int)(b); (i) < _b; ++i)
#define RANGE_R(i, a, b) for (int i = (int)b - 1, _a = (int)(a); (i) >= _a; --i)
#define MIN_UPDATE(target, value) target = min(target, value)
#define FOR(i, c)                                                              \
  for (__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define ALLR(c) (c).rbegin(), (c).rend()
#define PB push_back
#define MP(a, b) make_pair(a, b)
#define POPCOUNT(v) __builtin_popcountll((ll)(v))
#define IN_RANGE(v, a, b) ((a) <= (v) && (v) < (b))
#define CLEAR(table, v) memset(table, v, sizeof(table));
#define PRINT1(table, D0)                                                      \
  REP(d0, D0) cout << table[d0] << " ";                                        \
  cout << "\n";
#define PRINT2(table, D0, D1)                                                  \
  REP(d0, D0) {                                                                \
    REP(d1, D1) cout << table[d0][d1] << " ";                                  \
    cout << "\n";                                                              \
  }
#define PRINT3(table, D0, D1, D2)                                              \
  REP(d0, D0) {                                                                \
    REP(d1, D1) {                                                              \
      REP(d2, D2) cout << table[d0][d1][d2] << " ";                            \
      cout << "\n";                                                            \
    }                                                                          \
    cout << "\n";                                                              \
  }
#define DD(v) cout << #v << ": " << v << endl
template <typename T0, typename T1>
std::ostream &operator<<(std::ostream &os, const map<T0, T1> &v) {
  for (typename map<T0, T1>::const_iterator p = v.begin(); p != v.end(); p++) {
    os << p->first << ": " << p->second << " ";
  }
  return os;
}
template <typename T0, typename T1>
std::ostream &operator<<(std::ostream &os, const pair<T0, T1> &v) {
  os << v.first << ": " << v.second << " ";
  return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const vector<T> &v) {
  for (int i = 0; i < (int)v.size(); i++) {
    os << v[i] << " ";
  }
  return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const set<T> &v) {
  vector<T> tmp(v.begin(), v.end());
  os << tmp;
  return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const deque<T> &v) {
  vector<T> tmp(v.begin(), v.end());
  os << tmp;
  return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const vector<vector<T>> &v) {
  for (int i = 0; i < (int)v.size(); i++) {
    os << v[i] << endl;
  }
  return os;
}

/*

*/
int main() {
  int test_cases;
  cin >> test_cases;
  ll D, N, K, S;
  string s;
  REP(ttt, test_cases) {
    cin >> D >> N;
    //		DD(ttt);
    //		DD(D);
    //		DD(N);
    long double t = 0;
    REP(i, N) {
      cin >> K >> S;
      long double lt = ((long double)D - K) / S;
      //			DD(D-K);
      //			DD(S);
      //			DD(lt);
      //			printf("%.9Lf\n", lt);
      t = max(t, lt);
    }
    //		DD(t);
    long double ans = D / t;
    printf("Case #%d: %.9Lf\n", ttt + 1, ans);
    //		return 0;
  }
  return 0;
}
