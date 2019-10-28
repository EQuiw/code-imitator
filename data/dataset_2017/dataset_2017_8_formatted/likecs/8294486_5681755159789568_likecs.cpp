/******************************************
 *    AUTHOR:         BHUVNESH JAIN        *
 *    INSTITUITION:   BITS PILANI, PILANI  *
 ******************************************/
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

const int MAX = 105;

LL g[MAX][MAX];
vector<pll> go;
int n, q, u, v;
LD dp[MAX][MAX];
LL dis[MAX];

LD solve(int city, int last) {
  if (city == n) {
    return 0;
  }
  LD &res = dp[city][last];
  if (res < 0) {
    res = 1e18;
    LD can;
    LL sum = 0;
    for (int i = city; i < n; ++i) {
      sum += dis[i];
      if (sum <= go[city].first) {
        can = ((LD)sum) / ((LD)go[city].second);
        // printf("C : %d %d %Lf\n", i+1, city, can);
        can += solve(i + 1, i);
        res = min(res, can);
      }
    }
  }
  return res;
}

int main() {
  int t;
  scanf("%d", &t);
  for (int T = 1; T <= t; ++T) {
    printf("Case #%d: ", T);
    scanf("%d %d", &n, &q);
    go.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
      scanf("%lld %lld", &go[i].first, &go[i].second);
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        scanf("%lld", &g[i][j]);
        dp[i][j] = -1;
      }
      dis[i] = g[i][i + 1];
    }
    LD ans = 1e18, can;
    LL sum = 0;
    // printf("\n");
    for (int i = 1; i < n; ++i) {
      sum += dis[i];
      if (sum <= go[1].first) {
        can = ((LD)sum) / ((LD)go[1].second);
        // printf("C : %d %d %Lf\n", i + 1, i, can);
        can += solve(i + 1, i);
        // printf("%d : %Lf\n", i, can);
        ans = min(ans, can);
      }
    }
    while (q--) {
      scanf("%d %d", &u, &v);
      printf("%.10Lf\n", ans);
    }
  }
  return 0;
}