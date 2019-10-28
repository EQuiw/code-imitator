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
  long long W, H;
  for (int ttt = 0, _n = (test_cases); (ttt) < (int)_n; ++ttt) {
    cin >> H >> W;
    vector<string> m(H);
    for (int i = 0, _n = (H); (i) < (int)_n; ++i)
      cin >> m[i];
    for (int y = 0, _n = (H); (y) < (int)_n; ++y) {
      for (int x = 0, _n = (W); (x) < (int)_n; ++x) {
        if (m[y][x] == '?' && 0 <= x - 1 && m[y][x - 1] != '?')
          m[y][x] = m[y][x - 1];
      }
      for (int xx = 0, _n = (W); (xx) < (int)_n; ++xx) {
        int x = W - 1 - xx;
        if (m[y][x] == '?' && x + 1 < W && m[y][x + 1] != '?')
          m[y][x] = m[y][x + 1];
      }
    }
    for (int y = 0, _n = (H); (y) < (int)_n; ++y) {
      if (m[y][0] == '?' && 0 <= y - 1 && m[y - 1][0] != '?')
        m[y] = m[y - 1];
    }
    for (int yy = 0, _n = (H); (yy) < (int)_n; ++yy) {
      int y = H - 1 - yy;
      if (m[y][0] == '?' && y + 1 < H && m[y + 1][0] != '?')
        m[y] = m[y + 1];
    }
    int ans = 0;
    cout << "Case #" << ttt + 1 << ": " << endl;
    for (int y = 0, _n = (H); (y) < (int)_n; ++y) {
      cout << m[y] << endl;
    }
    //		return 0;
  }
  return 0;
}
