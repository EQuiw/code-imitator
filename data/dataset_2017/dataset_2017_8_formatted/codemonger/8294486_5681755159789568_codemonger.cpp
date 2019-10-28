#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t;
  cin >> t;

  for (int z = 1; z <= t; z++) {
    int n, q;
    cin >> n >> q;
    ll ee[n];
    ll ss[n];
    ll d[105][105];

    for (int i = 0; i < n; i++) {
      cin >> ee[i] >> ss[i];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> d[i][j];
      }
    }
    ll dist[n];
    dist[0] = 0;
    for (int i = 1; i < n; i++) {
      dist[i] = d[i - 1][i];
      dist[i] += dist[i - 1];
    }

    for (int i = 0; i < q; i++) {
      double dp[105];
      for (int j = 0; j < 105; j++) {
        dp[j] = 100000000000000.0;
      }
      int start, end;
      cin >> start >> end;
      dp[0] = 0.0;
      for (int j = 1; j < n; j++) {
        for (int k = 0; k < j; k++) {
          if (ee[k] >= (dist[j] - dist[k])) {
            double temp = (double)(dist[j] - dist[k]) / (double)ss[k];
            dp[j] = min(dp[j], (dp[k] + temp));
          }
        }
      }
      cout << "Case #" << z << ": ";
      printf("%.6f", dp[n - 1]);
      cout << endl;
    }
  }
}