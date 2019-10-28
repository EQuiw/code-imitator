#include <bits/stdc++.h>
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
  for (int i = curh; i < pos - 1; i++) {
    used += dist[i][i + 1];
  }
  double res = INF;
  for (int i = pos + 1; i < n; i++) {
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
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ;
  int T;

  cin >> T;

  for (int test = 1; test < T + 1; test++) {
    cout << "Case #" << test << ": ";
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
      cin >> e[i] >> s[i];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> dist[i][j];
      }
    }
    for (int i = 0; i < MAXN; i++)
      for (int j = 0; j < MAXN; j++) {
        dp[i][j] = -2.0;
      }
    int aa, aaa, aaaa;
    cin >> aa >> aaa;
    double res = go(0, 0);
    cout << setprecision(12) << fixed << res << endl;
  }

  return 0;
}
