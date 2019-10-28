#include <bits/stdc++.h>
using namespace std;
// const int inf = 0x7fffffff; //beware overflow
// const LL INF = 0x7fffffffffffffff; //beware overflow

template <typename A, typename B>
ostream &operator<<(ostream &s, const pair<A, B> &p) {
  return s << "(" << p.first << "," << p.second << ")";
}
template <typename T> ostream &operator<<(ostream &s, const vector<T> &c) {
  s << "[ ";
  for (auto it : c)
    s << it << " ";
  s << "]";
  return s;
}
template <typename T> ostream &operator<<(ostream &o, const set<T> &st) {
  o << "{";
  for (auto it = st.begin(); it != st.end(); it++)
    o << (it == st.begin() ? "" : ", ") << *it;
  return o << "}";
}
template <typename T1, typename T2>
ostream &operator<<(ostream &o, const map<T1, T2> &mp) {
  o << "{";
  for (auto it = mp.begin(); it != mp.end(); it++) {
    o << (it == mp.begin() ? "" : ", ") << it->first << ":" << it->second;
  }
  o << "}";
  return o;
}
inline long long getint() {
  long long _x = 0, _tmp = 1;
  char _tc = getchar();
  while ((_tc < '0' || _tc > '9') && _tc != '-')
    _tc = getchar();
  if (_tc == '-')
    _tc = getchar(), _tmp = -1;
  while (_tc >= '0' && _tc <= '9')
    _x *= 10, _x += (_tc - '0'), _tc = getchar();
  return _x * _tmp;
}

int R[100];
int Q[50][50];

void solve() {
  int n = getint(), p = getint();
  for (int i = 0; i < n; i++)
    R[i] = getint();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++)
      Q[i][j] = getint();
    sort(Q[i], Q[i] + p);
  }
  vector<vector<pair<int, int>>> vv(n, vector<pair<int, int>>(p));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < p; j++) {
      int f = (int)ceil(Q[i][j] * 1.0 / R[i] / 1.1);
      int s = (int)floor(Q[i][j] * 1.0 / R[i] / 0.9);
      if (f <= s)
        vv[i][j] = make_pair(f, s);
    }
  // cout << vv << endl;

  int ans = 0;

  vector<int> ptr(n, 0);
  for (int cur = 1; cur <= 1e6; cur++) {
    for (int i = 0; i < n; i++) {
      while (ptr[i] < ((int)(vv[i]).size()) && !(cur < vv[i][ptr[i]].first) &&
             !(cur >= vv[i][ptr[i]].first && cur <= vv[i][ptr[i]].second))
        ptr[i]++;
    }

    vector<int> used(n, 0);
    for (int i = 0; i < n; i++) {
      while (ptr[i] + used[i] < ((int)(vv[i]).size()) &&
             vv[i][ptr[i] + used[i]].first <= cur &&
             vv[i][ptr[i] + used[i]].second >= cur)
        used[i]++;
    }
    int tmp = *min_element(used.begin(), used.end());
    ans += tmp;
    for (int i = 0; i < n; i++)
      ptr[i] += tmp;

    for (int i = 0; i < n; i++)
      if (ptr[i] == ((int)(vv[i]).size()))
        break;
  }
  printf("%d\n", ans);
}
int main() {
  int T = getint();
  for (int testcase = 1; testcase <= T; testcase++) {
    printf("Case #%d: ", testcase);
    solve();
  }
}
