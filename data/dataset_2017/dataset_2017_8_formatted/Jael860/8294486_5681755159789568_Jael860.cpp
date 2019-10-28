#include <bits/stdc++.h>

#define debug(x) cerr << #x << ": " << x << endl;
#define print(x) cerr << x << endl;

#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define REP(i, x, y) for (int i = x; i < y; i++)
#define REPIT(it, A)                                                           \
  for (typeof(A.begin()) it = (A.begin()); it != A.end(); it++)
#define fst first
#define snd second
#define sqr(x) ((x) * (x))

#define fastio                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);
#define ones(x) __builtin_popcountll(x)
using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ii> vii;

const int MAXN = 150;
int n, q;
double dp[MAXN][MAXN];
ll e[MAXN], s[MAXN], dist[MAXN][MAXN], adist[MAXN][MAXN];
const double INF = 1e18;
double go(int pos, int curh) {
  if (pos == n - 1) {
    return 0.0;
  }
  if (dp[pos][curh] > -1.0)
    return dp[pos][curh];
  double len = 0.0;
  double used = 0.0;
  REP(i, curh, pos - 1) { used += dist[i][i + 1]; }
  double res = INF;
  REP(i, pos + 1, n) {
    len += dist[i - 1][i];
    double val = INF;
    if (len <= e[pos]) {
      // cerr<<"from "<<pos<<" "<<i<<endl;
      val = len / s[pos] + go(i, pos);
      res = min(res, val);
    }
    if (used + len <= e[curh]) {
      // cerr<<pos<<" "<<i<<endl;
      val = len / s[curh] + go(i, curh);

      res = min(res, val);
    }
  }
  // cerr<<"ans "<<pos<<" "<<curh<<" "<<res<<endl;
  return dp[pos][curh] = res;
}

int main() {
  fastio;
  int T;

  cin >> T;

  REP(test, 1, T + 1) {
    cout << "Case #" << test << ": ";
    cin >> n >> q;
    REP(i, 0, n) { cin >> e[i] >> s[i]; }
    REP(i, 0, n) {
      REP(j, 0, n) { cin >> dist[i][j]; }
    }
    REP(i, 0, MAXN) REP(j, 0, MAXN) { dp[i][j] = -2.0; }
    int aa, aaa, aaaa;
    cin >> aa >> aaa;
    double res = go(0, 0);
    cout << setprecision(12) << fixed << res << endl;
  }

  return 0;
}
