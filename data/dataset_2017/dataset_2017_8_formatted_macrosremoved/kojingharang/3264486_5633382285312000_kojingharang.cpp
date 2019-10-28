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

string tos(long long N) {
  stringstream ss;
  ss << N;
  return ss.str();
}

long long toll(string s) {
  stringstream ss;
  ss << s;
  long long N;
  ss >> N;
  return N;
}

bool isTidy(long long N) {
  stringstream ss;
  ss << N;
  string s = ss.str();
  for (int i = 0, _n = (s.size() - 1); (i) < (int)_n; ++i) {
    if (s[i] > s[i + 1])
      return false;
  }
  return true;
}

long long naive(long long N) {
  for (long long i = N; i >= 1; i--) {
    if (isTidy(i))
      return i;
  }
  return 1;
}

long long solve(long long N) {
  string s = tos(N);
  for (int i = 0, _n = (s.size() - 1); (i) < (int)_n; ++i) {
    if (s[i] > s[i + 1]) {
      s[i]--;
      for (int j = (int)i + 1, _b = (int)(s.size()); (j) < _b; ++j)
        s[j] = '9';
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
  long long N;
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

  for (int ttt = 0, _n = (test_cases); (ttt) < (int)_n; ++ttt) {
    cin >> N;
    //		ll nans = naive(N);
    long long ans = solve(N);
    //		assert(nans==ans);
    cout << "Case #" << ttt + 1 << ": " << ans << endl;
    //		return 0;
  }
  return 0;
}
