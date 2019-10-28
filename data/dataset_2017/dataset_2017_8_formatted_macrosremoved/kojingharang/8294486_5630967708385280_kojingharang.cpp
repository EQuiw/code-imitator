#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <vector>

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
  long long D, N, K, S;
  string s;
  for (int ttt = 0, _n = (test_cases); (ttt) < (int)_n; ++ttt) {
    cin >> D >> N;
    //		DD(ttt);
    //		DD(D);
    //		DD(N);
    long double t = 0;
    for (int i = 0, _n = (N); (i) < (int)_n; ++i) {
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
