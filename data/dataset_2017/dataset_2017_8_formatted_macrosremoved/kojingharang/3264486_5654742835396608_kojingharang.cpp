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

vector<long long> put(const vector<long long> &w) {
  long long N = w.size();
  long long bi = -1;
  long long bMin = -1;
  long long bMax = -1;
  for (int i = 0, _n = (N); (i) < (int)_n; ++i) {
    if (w[i])
      continue;
    long long Ls = 0, Rs = 0;
    for (int j = i - 1; j >= 0; j--)
      if (w[j])
        break;
      else
        Ls++;
    for (int j = i + 1; j < N; j++)
      if (w[j])
        break;
      else
        Rs++;
    long long Min = min(Ls, Rs);
    long long Max = max(Ls, Rs);
    if (bMin < Min || (bMin == Min && bMax < Max)) {
      bMin = Min;
      bMax = Max;
      bi = i;
    }
  }
  assert(bi >= 0);
  return {bi, bMin, bMax};
}

// return: min, max
vector<long long> naive(long long N, long long K) {
  vector<long long> w(N);
  vector<long long> c;
  for (int i = 0, _n = (K); (i) < (int)_n; ++i) {
    c = put(w);
    //		DD(c[0]);
    w[c[0]] = 1;
    //		DD(w);
  }
  return {c[1], c[2]};
}

int main() {
  int test_cases;
  cin >> test_cases;
  long long N, K;
  string s;
  for (int ttt = 0, _n = (test_cases); (ttt) < (int)_n; ++ttt) {
    cin >> N >> K;
    auto ans = naive(N, K);
    cout << "Case #" << ttt + 1 << ": " << ans[1] << " " << ans[0] << endl;
    //		return 0;
  }
  return 0;
}
