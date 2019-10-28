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
  long long N, P;
  string s;
  for (int ttt = 0, _n = (test_cases); (ttt) < (int)_n; ++ttt) {
    cin >> N >> P;
    vector<long long> g(N);
    vector<vector<long long>> p(N, vector<long long>(P));
    for (int i = 0, _n = (N); (i) < (int)_n; ++i)
      cin >> g[i];
    for (int i = 0, _n = (N); (i) < (int)_n; ++i) {
      for (int j = 0, _n = (P); (j) < (int)_n; ++j)
        cin >> p[i][j];
    }
    long long ans = 0;
    for (int cnt = (int)1, _b = (int)(1000001); (cnt) < _b; ++cnt) {
      while (1) {
        vector<long long> use(N, -1);
        for (int i = 0, _n = (N); (i) < (int)_n; ++i) {
          for (int pi = 0, _n = (P); (pi) < (int)_n; ++pi) {
            if (p[i][pi] && g[i] * cnt * 90 <= p[i][pi] * 100 &&
                p[i][pi] * 100 <= g[i] * cnt * 110) {
              use[i] = pi;
              break;
            }
          }
        }
        bool ok = find((use).begin(), (use).end(), -1) == use.end();
        if (ok) {
          for (int i = 0, _n = (N); (i) < (int)_n; ++i)
            p[i][use[i]] = 0;
          ans++;
        } else
          break;
      }
    }
    cout << "Case #" << ttt + 1 << ": " << ans << endl;
    //		return 0;
  }
  return 0;
}
