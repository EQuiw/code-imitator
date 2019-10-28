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
  long long N, R, O, Y, G, B, V;
  string s;
  for (int ttt = 0, _n = (test_cases); (ttt) < (int)_n; ++ttt) {
    cin >> N >> R >> O >> Y >> G >> B >> V;
    vector<pair<int, char>> h = {
        {R, 'R'},
        {Y, 'Y'},
        {B, 'B'},
    };
    sort((h).begin(), (h).end());
    string ans = "IMPOSSIBLE";
    if (h[2].first <= h[0].first + h[1].first) {
      ans = "";
      long long As = h[2].first;
      vector<vector<string>> w(3, vector<string>(As));
      for (int i = 0, _n = (As); (i) < (int)_n; ++i) {
        w[0][i] = string(1, h[2].second);
        w[1][i] = i < h[0].first ? string(1, h[0].second) : "";
        w[2][i] = (As - 1 - i) < h[1].first ? string(1, h[1].second) : "";
      }
      for (int i = 0, _n = (As); (i) < (int)_n; ++i) {
        for (int j = 0, _n = (3); (j) < (int)_n; ++j)
          ans += w[j][i];
      }
    }
    cout << "Case #" << ttt + 1 << ": " << ans << endl;
    //		return 0;
  }
  return 0;
}
