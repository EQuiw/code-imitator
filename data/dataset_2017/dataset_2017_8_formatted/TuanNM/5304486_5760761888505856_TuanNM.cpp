#include <bits/stdc++.h>
#define TR(c, it) for (__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define FOR(i, a, b) for (int i = (a), _b = (b); i < _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define FORE(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define SZ(c) (int)(c).size()

using namespace std;

const int N = 30;

string s[N];
int rr, cc;
int a[N], b[N];
int c[N], d[N];
int m = 0;
char patterns[N];

void fillBoad(int x, int y, int u, int v, int t) {
  FORE(i, x, u) {
    FORE(j, y, v) { s[i][j] = 'A' + t; }
  }
}
bool invalid(int a, int b, int c, int d, int x, int y) {
  // x, y, nam trong
  return (a <= x && x <= c && b <= y && y <= d);
}

bool check(int u, int v, int t) {
  int aa = a[t];
  int bb = b[t];
  int cc = c[t];
  int dd = d[t];
  aa = min(aa, u);
  bb = min(bb, v);
  cc = max(cc, u);
  dd = max(dd, v);
  for (int i = 0; i < m; ++i) {
    int ch = patterns[i];
    if (ch == t)
      continue;
    if (invalid(a[ch], b[ch], c[ch], d[ch], aa, bb))
      return false;
    if (invalid(a[ch], b[ch], c[ch], d[ch], cc, dd))
      return false;
    if (invalid(aa, bb, cc, dd, a[ch], b[ch]))
      return false;
    if (invalid(aa, bb, cc, dd, c[ch], d[ch]))
      return false;
  }
  return true;
}

int main() {
  // freopen("A.inp", "r", stdin);
  // freopen("A.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int nTest;
  cin >> nTest;
  for (int test = 1; test <= nTest; ++test) {
    cout << "Case #" << test << ":" << endl;
    cin >> rr >> cc;
    m = 0;
    memset(a, 0x3f, sizeof a);
    memset(b, 0x3f, sizeof b);
    memset(c, 0xff, sizeof c);
    memset(d, 0xff, sizeof d);
    for (int i = 0; i < rr; ++i) {
      cin >> s[i];
      for (int j = 0; j < cc; ++j)
        if (s[i][j] != '?') {
          int u = s[i][j] - 'A';
          patterns[m++] = u;
          a[u] = min(a[u], i);
          b[u] = min(b[u], j);
          c[u] = max(c[u], i);
          d[u] = max(d[u], j);
        }
    }
    for (int i = 0; i < m; ++i) {
      int u = patterns[i];
      fillBoad(a[u], b[u], c[u], d[u], u);
    }
    for (int i = 0; i < rr; ++i) {
      for (int j = 0; j < cc; ++j)
        if (s[i][j] == '?') {
          for (int k = 0; k < m; ++k) {
            int u = patterns[k];
            if (check(i, j, u)) {
              a[u] = min(a[u], i);
              b[u] = min(b[u], j);
              c[u] = max(c[u], i);
              d[u] = max(d[u], j);
              break;
            }
          }
        }
    }
    for (int i = 0; i < m; ++i) {
      int u = patterns[i];
      fillBoad(a[u], b[u], c[u], d[u], u);
    }
    for (int i = 0; i < rr; ++i) {
      cout << s[i] << endl;
    }
  }
  return 0;
}
