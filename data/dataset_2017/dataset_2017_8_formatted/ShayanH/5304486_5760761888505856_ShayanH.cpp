#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define SQR(a) ((a) * (a))
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define CLR(x, a) memset(x, a, sizeof x)
#define VAL(x) #x << " = " << (x) << "   "
#define FOREACH(i, x)                                                          \
  for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
#define FOR(i, n) for (int i = 0; i < (n); i++)
#define X first
#define Y second

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const int MAXN = 30;

char a[MAXN][MAXN];
int n, m;
int d[MAXN][MAXN];
bool mark[MAXN][MAXN];

void colorize(int x1, int y1, int x2, int y2, char c) {
  for (int i = x1; i <= x2; i++)
    for (int j = y1; j <= y2; j++) {
      mark[i][j] = true;
      a[i][j] = c;
    }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      d[i][j] = (a[i][j] != '?');
      if (i > 0)
        d[i][j] += d[i - 1][j];
      if (j > 0)
        d[i][j] += d[i][j - 1];
      if (i > 0 && j > 0)
        d[i][j] -= d[i - 1][j - 1];
    }
}

bool check(int x1, int y1, int x2, int y2) {
  int res = d[x2][y2];
  if (x1 > 0)
    res -= d[x1 - 1][y2];
  if (y1 > 0)
    res -= d[x2][y1 - 1];
  if (x1 > 0 && y1 > 0)
    res += d[x1 - 1][y1 - 1];
  return (res == 1);
}

void go(int x, int y) {
  for (int i1 = 0; i1 <= x; i1++)
    for (int j1 = 0; j1 <= y; j1++)
      for (int i2 = n - 1; i2 >= x; i2--)
        for (int j2 = m - 1; j2 >= y; j2--)
          if (check(i1, j1, i2, j2)) {
            colorize(i1, j1, i2, j2, a[x][y]);
            return;
          }
}

int main() {
  ios::sync_with_stdio(false);

  int tc;
  cin >> tc;
  for (int tt = 1; tt <= tc; tt++) {
    CLR(d, 0);
    CLR(mark, 0);
    cout << "Case #" << tt << ":" << endl;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        cin >> a[i][j];

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) {
        d[i][j] = (a[i][j] != '?');
        if (i > 0)
          d[i][j] += d[i - 1][j];
        if (j > 0)
          d[i][j] += d[i][j - 1];
        if (i > 0 && j > 0)
          d[i][j] -= d[i - 1][j - 1];
      }

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (a[i][j] != '?' && !mark[i][j]) {
          go(i, j);
        }

    for (int i = 0; i < n; i++, cout << endl)
      for (int j = 0; j < m; j++)
        cout << a[i][j];
  }
  return 0;
}
