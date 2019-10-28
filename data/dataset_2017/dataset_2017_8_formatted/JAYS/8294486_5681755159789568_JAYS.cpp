#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

const ll INF = 1LL << 50;

int N, Q;
ll E[105], S[105], D[105][105];
int U[105], V[105];

double dp[105][105];
double rec(int city, int horse) {
  double &ret = dp[city][horse];
  if (ret != -1.0)
    return ret;
  if (city == N) {
    ll distance = 0;
    for (int i = horse; i < city; i++) {
      distance += D[i][i + 1];
    }
    if (distance > E[horse])
      return ret = INF;
    else
      ret = 0.0;
  }
  ret = INF;
  double t1 = ((double)D[city][city + 1]) / S[horse];
  double t2 = ((double)D[city][city + 1]) / S[city];
  ret = min(ret, t1 + rec(city + 1, horse));
  ret = min(ret, t2 + rec(city + 1, city));
  return ret;
}

double solve() {
  for (int i = 0; i < 105; i++)
    for (int j = 0; j < 105; j++)
      dp[i][j] = -1.0;
  return rec(1, 1);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++)
      scanf("%lld%lld", E + i, S + i);
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++)
        scanf("%lld", &D[i][j]);
    }
    for (int i = 1; i <= Q; i++)
      scanf("%d%d", U + i, V + i);
    double ans = solve();
    printf("Case #%d: %.9lf\n", t, ans);
  }
  return 0;
}