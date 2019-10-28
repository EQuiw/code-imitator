#include <bits/stdc++.h>
using namespace std;
//#define DEBUG
typedef pair<int, int> pii;
typedef long long ll;

template <typename Iter> ostream &_out(ostream &s, Iter a, Iter b) {
  for (auto it = a; it != b; it++)
    s << (it == a ? "" : " ") << *it;
  return s;
}

template <typename A, typename B>
ostream &operator<<(ostream &s, pair<A, B> &p) {
  return s << "(" << p.first << " , " << p.second << ")";
}
template <typename T> ostream &operator<<(ostream &s, vector<T> &v) {
  return _out(s, v.begin(), v.end());
}

inline ll rit() {
  int key = 1;
  char c = getchar();
  while (!isdigit(c)) {
    if (c == '-')
      key = -1;
    c = getchar();
  }

  ll x = 0;
  while (isdigit(c)) {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return x * key;
}

int __ = 1;

/*********default*********/

void init() {}

void read() {}

void solve() {}

double k[1010], s[1010];

int main() {
  int test, n, kase = 0;
  double d;
  scanf("%d", &test);
  while (test--) {
    scanf("%lf%d", &d, &n);
    for (int i = 0; i < n; i++) {
      scanf("%lf%lf", &k[i], &s[i]);
    }

    double ans = 0;
    for (int i = 0; i < n; i++) {
      ans = max(ans, (d - k[i]) / s[i]);
    }

    printf("Case #%d: %.8lf\n", ++kase, d / ans);
  }
  return 0;
}
