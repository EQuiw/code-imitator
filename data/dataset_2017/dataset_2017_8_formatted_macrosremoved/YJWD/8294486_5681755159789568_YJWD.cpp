#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

typedef long long LL;
typedef pair<int, int> P;
const LL inf = 1LL << 61;
const LL mod = 1000000007;

const int maxn = 110;

int n;
double mat[maxn][maxn];
double dp[maxn];
double left_dis[maxn];
double e_arr[maxn], s_arr[maxn];
int arriv_idx[maxn];
void dfs(int m, double tpdp, double leftd, int idx);
int main() {

  // std::ios::sync_with_stdio(false);
  int i = 0, j = 0, k = 0, kase = 0;
  int t, q;
  double len;
  freopen("C-small-attempt1.in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; i++) {
      scanf("%lf%lf", &e_arr[i], &s_arr[i]);
      // Debug(e_arr[i]);
    }
    for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++) {
        scanf("%lf", &mat[i][j]);
      }
    }
    int u, v;
    for (i = 1; i <= q; i++) {
      scanf("%d%d", &u, &v);
    }
    for (i = 1; i <= n; i++) {
      dp[i] = 1e12;
    }
    // arriv_idx[1] = 1;
    // left_dis[1] = e_arr[1];
    dp[1] = 0;
    dfs(1, 0.0, e_arr[1], 1);
    printf("Case #%d: %.8lf\n", ++kase, dp[n]);
  }

  return 0;
}
void dfs(int m, double tpdp, double leftd,
         int idx) { // cout << m << " " << leftd << endl;
  int i;
  for (i = 1; i <= n; i++) {
    if (i == m)
      continue;
    if (mat[m][i] < 0)
      continue;
    if (leftd < mat[m][i])
      continue;
    double tp = tpdp + mat[m][i] / s_arr[idx];
    if (tp < dp[i]) {
      dp[i] = tp;
      dfs(i, dp[i], leftd - mat[m][i], idx);
      dfs(i, dp[i], e_arr[i], i);
    } else {
      dfs(i, tp, leftd - mat[m][i], idx);
    }
  }
}
