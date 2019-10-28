#include <bits/stdc++.h>
using namespace std;
typedef pair<long long int, long long int> PI;
typedef pair<long long int, long long int> PI;

long long int e[111];
long long int s[111];
long long int d[111][111];
long long int n, q;
long long int from, to;

// dp[i][j] : i番目の町までj番目の馬で来るときの最小時間
double dp[111][111];
// dp2[i] :
// なんでもいいからi番目の町につくときの最小時間（馬のりかえる時に参照）
double dp2[111];
long long int sum_distance[111];

inline double calc() {
  // まず2点間距離計算をなんとかする
  sum_distance[0] = 0;
  for (long long int i = 0; i < ((long long int)(n - 1)); i++) {
    sum_distance[i + 1] = sum_distance[i] + d[i][i + 1];
  }
  dp[0][0] = 0;
  dp2[0] = 0;
  for (long long int i = (long long int)(1); i < ((long long int)(n)); i++) {
    dp2[i] = (1ll << (long long int)(60));
    for (long long int j = 0; j < ((long long int)(i)); j++) {
      // j番目の町の馬でここまでくる
      dp[i][j] = (1ll << (long long int)(60));
      const long long int dd = sum_distance[i] - sum_distance[j];
      if (dd <= e[j]) {
        double tmp_part_time = dd * 1.0 / s[j];
        dp[i][j] = dp2[j] + tmp_part_time;
        dp2[i] = min(dp2[i], dp[i][j]);
      }
    }
  }
  return dp2[n - 1];
}

inline void solve() {
  cin >> n >> q;
  for (long long int i = 0; i < ((long long int)(n)); i++) {
    cin >> e[i] >> s[i];
  }
  for (long long int i = 0; i < ((long long int)(n)); i++) {
    for (long long int j = 0; j < ((long long int)(n)); j++)
      cin >> d[i][j];
  }
  for (long long int i = 0; i < ((long long int)(q)); i++) {
    cin >> from >> to;
    printf("%.12f\n", calc());
  }
}

int main() {
  long long int t;
  cin >> t;
  for (long long int case_num = 0; case_num < ((long long int)(t));
       case_num++) {
    cout << "Case #" << case_num + 1 << ": ";
    solve();
  }

  return 0;
}
