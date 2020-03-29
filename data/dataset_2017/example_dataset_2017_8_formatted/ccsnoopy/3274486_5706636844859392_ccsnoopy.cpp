#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#ifdef DEBUG
#define cek(x) cout << x
#else
#define cek(x)                                                                 \
  if (false) {                                                                 \
  }
#endif // DEBUG

#define fi first
#define se second
#define INF 1000000000
#define INFLL 1000000000000000000LL
#define EPS 1e-9
#define PI acos(-1.0)
#define pb push_back
#define TC() while (tc--)
#define FOR(i, n) for (int i = 0; i < n; i++)
#define FORN(i, n) for (int i = 0; i <= n; i++)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define REPN(i, a, b) for (int i = a; i <= b; i++)
#define reset(a, b) memset(a, b, sizeof(a))
#define ALL(v) v.begin(), v.end()
#define SORT(v) sort(ALL(v))
#define SORTA(v, n) sort(v, v + n)
#define SZ(v) (int)v.size()
#define sc(x) scanf("%d", &x)

void open() {
  freopen("D:/OneDrive/Code/GCJ/B-small-attempt0 (3).in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

int ac[1500];
int aj[1500];
int memo[1500][730][2][2];

int dp(int minute, int left, int cur, int st_with) {
  if (minute == 1440) {
    if (left != 0)
      return 10000;
    if (cur == st_with)
      return 0;
    return 1;
  }

  if (memo[minute][left][cur][st_with] != -1)
    return memo[minute][left][cur][st_with];

  int ans = 10000;

  if (cur == 0) {
    if (ac[minute]) {
      ans = dp(minute + 1, left, 1, st_with) + 1;
    } else {
      if (left > 0) {
        ans = dp(minute + 1, left - 1, 0, st_with);
      }
      if (!aj[minute]) {
        ans = min(ans, dp(minute + 1, left, 1, st_with) + 1);
      }
    }
  } else {
    if (aj[minute]) {
      if (left > 0) {
        ans = dp(minute + 1, left - 1, 0, st_with) + 1;
      }
    } else {
      ans = dp(minute + 1, left, 1, st_with);
      if (!ac[minute] && left > 0) {
        ans = min(ans, dp(minute + 1, left - 1, 0, st_with) + 1);
      }
    }
  }

  return memo[minute][left][cur][st_with] = ans;
}

int main(void) {
  open();
  int tc;
  sc(tc);

  for (int ct = 1; ct <= tc; ct++) {
    int c, j;
    sc(c);
    sc(j);

    reset(ac, false);
    reset(aj, false);
    reset(memo, -1);

    FOR(i, c) {
      int st, en;
      sc(st);
      sc(en);
      for (int j = st; j < en; j++)
        ac[j] = true;
    }

    FOR(i, j) {
      int st, en;
      sc(st);
      sc(en);
      for (int j = st; j < en; j++)
        aj[j] = true;
    }
    int ans = INF;
    if (!ac[0]) {
      ans = min(ans, dp(1, 719, 0, 0));
    }

    if (!aj[0]) {
      ans = min(ans, dp(1, 720, 1, 1));
    }

    printf("Case #%d: %d\n", ct, ans);

    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
