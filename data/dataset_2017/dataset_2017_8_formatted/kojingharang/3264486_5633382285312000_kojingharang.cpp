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

string tos(ll N) {
  stringstream ss;
  ss << N;
  return ss.str();
}

ll toll(string s) {
  stringstream ss;
  ss << s;
  ll N;
  ss >> N;
  return N;
}

bool isTidy(ll N) {
  stringstream ss;
  ss << N;
  string s = ss.str();
  REP(i, s.size() - 1) {
    if (s[i] > s[i + 1])
      return false;
  }
  return true;
}

ll naive(ll N) {
  for (ll i = N; i >= 1; i--) {
    if (isTidy(i))
      return i;
  }
  return 1;
}

ll solve(ll N) {
  string s = tos(N);
  REP(i, s.size() - 1) {
    if (s[i] > s[i + 1]) {
      s[i]--;
      RANGE(j, i + 1, s.size()) s[j] = '9';
      //			DD(s);
      //			DD(toll(s));
      return solve(toll(s));
    }
  }
  return N;
}

int main() {
  int test_cases;
  cin >> test_cases;
  ll N;
  //	RANGE(i, 1, 100000) {
  //		ll nans = naive(i);
  //		ll ans = solve(i);
  ////		DD(i);
  ////		DD(nans);
  ////		DD(ans);
  //		if(nans!=ans) {
  //			DD(i);
  //			DD(nans);
  //			DD(ans);
  //			assert(nans==ans);
  //		}
  //	}
  //	return 0;

  REP(ttt, test_cases) {
    cin >> N;
    //		ll nans = naive(N);
    ll ans = solve(N);
    //		assert(nans==ans);
    cout << "Case #" << ttt + 1 << ": " << ans << endl;
    //		return 0;
  }
  return 0;
}
