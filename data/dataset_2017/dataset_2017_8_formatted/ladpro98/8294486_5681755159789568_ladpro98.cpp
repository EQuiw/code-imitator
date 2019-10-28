#include <bits/stdc++.h>

using namespace std;

const int N = 111;

int max_dist[N];
int speed[N];
int start[N], finish[N];
int d[N][N];

int n, q;

bool is_small_dataset() {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j)
      if (i + 1 != j) {
        if (d[i][j] != -1)
          return false;
      }
  }
  if (q != 1)
    return false;
  if (start[1] != 1)
    return false;
  if (finish[1] != n)
    return false;
  return true;
}

void do_small(int tc) {
  vector<double> dp(n + 1, 1e18);
  dp[1] = 0;
  for (int i = 1; i < n; ++i) {
    long long sum_dist = 0;
    for (int j = i; j < n; ++j) {
      sum_dist += d[j][j + 1];
      if (sum_dist > max_dist[i])
        break;
      dp[j + 1] = min(dp[j + 1], dp[i] + 1.0 * sum_dist / speed[i]);
    }
  }
  cout << setprecision(6) << fixed << "Case #" << tc << ": " << dp[n] << endl;
}

int main() {
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
      cin >> max_dist[i];
      cin >> speed[i];
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        cin >> d[i][j];
      }
    }
    for (int i = 1; i <= q; ++i) {
      cin >> start[i] >> finish[i];
    }

    if (is_small_dataset()) {
      do_small(tc);
    } else {
      // do_large();
    }
  }
  return 0;
}