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

char s[1005];
int main() {
  int T = getint();
  for (int testcase = 1; testcase <= T; testcase++) {
    printf("Case #%d: ", testcase);
    int k;
    scanf("%s %d", s, &k);
    int n = strlen(s);
    int move = 0;
    int i;
    for (i = 0; i < n; i++) {
      if (s[i] == '-') {
        if (i + k - 1 >= n) {
          printf("IMPOSSIBLE\n");
          break;
        }
        move++;
        for (int j = 0; j < k; j++)
          s[i + j] ^= ('+' ^ '-');
      }
    }
    if (i == n)
      printf("%d\n", move);
  }
}
