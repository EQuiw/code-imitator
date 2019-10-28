#include <bits/stdc++.h>
#define INF 10000000000000ll
using namespace std;
int n, q;
int u, v;
long long dis[1005][1005];
struct Horse {
  int maxDis, speed;
} horse[1005];

void init() {
  memset(dis, 0, sizeof(dis));
  memset(horse, 0, sizeof(horse));
}
double dp[1005][1005]; // dp[i][j]表示用第j匹马到达第i个点，最小的时间

int main() {
  int t;
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("C-small-attempt0.out", "w", stdout);
  cin >> t;
  for (int I = 1; I <= t; I++) {
    printf("Case #%d: ", I);
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
      cin >> horse[i].maxDis >> horse[i].speed;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        cin >> dis[i][j];
    long long dis2[1005] = {0};
    for (int i = 1; i < n; i++)
      dis2[i] = dis[i][i + 1];
    cin >> u >> v;
    memset(dp, 127, sizeof(dp));
    dp[0][1] = dp[1][1] = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= i; j++) {
        long long Dis = 0;
        for (int k = j; k < i; k++)
          Dis += dis2[k];
        if (Dis > horse[j].maxDis) {
          dp[i][j] = INF;
          continue;
        }
        if (i != j)
          dp[i][j] = dp[i - 1][j] + 1.0 * dis2[i - 1] / horse[j].speed;
        else
          for (int k = 1; k < i; k++)
            dp[i][j] = min(dp[i][j], dp[i][k]);
      }
    // cout<<dp[n][n]<<endl;
    printf("%.6lf\n", dp[n][n]);
  }
  return 0;
}
