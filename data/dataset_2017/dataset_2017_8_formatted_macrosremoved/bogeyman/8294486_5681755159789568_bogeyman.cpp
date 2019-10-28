#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <regex>
#include <set>
#include <stack>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int S = int(1e2) + 10;
const double INF = 1e15 + 7;
const ll MOD = ll(1e9) + 7;
const double EPS = 1e-12;
const ll magic = ll(5e4);

ll e[S], s[S], dd[S], d[S], qq, f[S][S];
int n, T;
double dp[S];

int main() {
  freopen("/Users/user/Downloads/C-small-attempt1.in", "r", stdin);
  freopen("key.out", "w", stdout);
  cin >> T;
  //	printf("Case #%d: IMPOSSIBLE\n", q);
  for (int q = 1; q <= T; q++) {
    cin >> n >> qq;
    for (int i = 0; i < n; i++) {
      scanf("%lld%lld", e + i, s + i);
      dp[i] = INF;
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        //				if(j == i + 1)
        scanf("%lld", &f[i][j]);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (j == i + 1)
          dd[i] = f[i][j];
    d[1] = dd[0];
    for (int i = 2; i < n; i++)
      d[i] = d[i - 1] + dd[i - 1];

    cin >> qq >> qq;
    dp[n - 1] = 0;
    for (int i = n - 2; i >= 0; i--)
      for (int j = i + 1; j < n; j++)
        if (d[j] - d[i] <= e[i])
          dp[i] = min(dp[i], double(d[j] - d[i]) / s[i] + dp[j]);

    printf("Case #%d: %lf\n", q, dp[0]);
  }
  return 0;
}
