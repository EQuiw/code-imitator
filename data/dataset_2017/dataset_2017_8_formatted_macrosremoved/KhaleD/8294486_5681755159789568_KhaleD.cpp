#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef set<int> si;
typedef map<int, int> mii;

const int N = 102;
int t, n, q, dist[N], speed[N], u, v;
vector<vector<pii>> g(N);
bool vis[N];
double dp[N];

double solve(int i) {
  if (i == v)
    return 0;
  if (!((int)(g[i]).size()))
    return 1000000000000000000ll;
  if (vis[i])
    return dp[i];
  vis[i] = true;

  dp[i] = 1000000000000000000ll;
  double totalDist = g[i].back().second;
  int j = g[i].back().first;
  while (totalDist <= dist[i]) {
    dp[i] = min(dp[i], totalDist / speed[i] + solve(j));
    if (j == v)
      break;
    if (!((int)(g[j]).size()))
      return dp[i];
    totalDist += g[j].back().second;
    j = g[j].back().first;
  }
  return dp[i];
}

int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d", &t);
  for (int test = (1); test <= (int)(t); ++test) {
    scanf("%d%d", &n, &q);
    for (int i = (1); i <= (int)(n); ++i)
      scanf("%d%d", &dist[i], &speed[i]);
    for (int i = (1); i <= (int)(n); ++i)
      for (int j = (1); j <= (int)(n); ++j) {
        int a;
        scanf("%d", &a);
        if (a != -1)
          g[i].push_back(make_pair(j, a));
      }
    while (q--) {
      scanf("%d%d", &u, &v);
      memset(vis, 0, sizeof vis);
      printf("Case #%d: %.6f\n", test, solve(u));
    }

    g.clear(), g.resize(N);
  }
}

// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);
// ios::sync_with_stdio(0);cin.tie(0);
