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

long long E[500], S[500];
long long D[500][500];
int U[500], K[500];
double tt[500][500];
double dp[500];
void floyd(int n) {
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
}
int main() {
  int T = getint();
  for (int testcase = 1; testcase <= T; testcase++) {
    printf("Case #%d: ", testcase);
    int n = getint(), q = getint();
    ;
    for (int i = 0; i < n; i++) {
      E[i] = getint(), S[i] = getint();
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        D[i][j] = getint();
        if (D[i][j] == -1)
          D[i][j] = 1e15;
        if (i == j)
          D[i][j] = 0;
      }
    floyd(n);
    /*
    for(int i=0; i<n; i++) for(int j=0;j<n;j++) {
        if(
        tt[i][j] =
    }
    */
    for (int i = 0; i < q; i++)
      scanf("%d %d", &U[i], &K[i]);

    dp[0] = 0;
    for (int i = 1; i < n; i++) {
      dp[i] = 1e15;
      for (int j = 0; j < i; j++) {
        dp[i] = min(dp[i],
                    dp[j] + ((D[j][i] > E[j]) ? 1e15 : 1.0 * D[j][i] / S[j]));
      }
    }
    printf("%.6f\n", dp[n - 1]);
  }
}
