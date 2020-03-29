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
  freopen("D:/OneDrive/Code/GCJ/A-small-attempt0.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

int n, k;

double memo[1010][1010];

pair<double, double> pancake[1010];

double tinggiarea(int idx) {
  // cout << idx << " " << 2.0 * PI * pancake[idx].first * pancake[idx].second
  // << endl;
  return 2.0 * PI * pancake[idx].first * pancake[idx].second;
}

double base(int idx) {
  // cout << PI * pancake[idx].first * pancake[idx].second << endl;
  return PI * pancake[idx].first * pancake[idx].first;
}

double dp(int idx, int sisa) {
  if (sisa == 0)
    return 0;
  if (idx < 0)
    return -INF;
  if (memo[idx][sisa] >= 0)
    return memo[idx][sisa];

  double ans = 0;
  if (sisa == k) {
    ans = max(dp(idx - 1, sisa),
              dp(idx - 1, sisa - 1) + tinggiarea(idx) + base(idx));
  } else if (sisa > 0) {
    ans = max(dp(idx - 1, sisa), dp(idx - 1, sisa - 1) + tinggiarea(idx));
  }

  return memo[idx][sisa] = ans;
}

int main(void) {
  open();
  int tc;
  sc(tc);

  for (int ct = 1; ct <= tc; ct++) {
    sc(n);
    sc(k);
    for (int i = 0; i < n; i++) {
      cin >> pancake[i].first >> pancake[i].second;
    }

    FORN(i, 1001) FORN(j, 1001) memo[i][j] = -1.0;

    sort(pancake, pancake + n);
    printf("Case #%d: %.10lf\n", ct, dp(n - 1, k));

    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
