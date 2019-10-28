#include <algorithm> // sort
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef long long ll;
using namespace std;

int main() {
  ll T;
  cin >> T;

  for (int t = 0; t < T; t++) {
    ll N, Q;
    cin >> N >> Q;

    vector<ll> Es(N);
    vector<ll> Ss(N);
    for (int i = 0; i < N; i++) {
      cin >> Es[i] >> Ss[i];
    }
    vector<vector<ll>> Ds(N);
    for (int i = 0; i < N; i++) {
      Ds[i].resize(N);
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> Ds[i][j];
      }
    }
    vector<pair<int, int>> UVs(Q);
    for (int i = 0; i < Q; i++) {
      int u, v;
      cin >> u >> v;
      UVs[i] = make_pair(u, v);
    }

    // small : Q=0
    vector<ll> Dss(N, 0); // distance sum from city 1
    for (int i = 1; i < N; i++) {
      Dss[i] = Dss[i - 1] + Ds[i - 1][i];
    }

    vector<vector<double>> dp(
        N); // min time which @ city i with horse j, -1 if impossible
    for (int i = 0; i < N; i++) {
      dp[i].resize(N);
    }
    dp[1][0] = (double)Ds[0][1] / (double)Ss[0];
    for (int i = 2; i < N; i++) { // city
      // horse, change horse
      double min_time = numeric_limits<double>::max();
      for (int k = 0; k < i - 1; k++) {
        if (dp[i - 1][k] >= 0) {
          min_time = min(min_time, dp[i - 1][k]);
        }
      }
      dp[i][i - 1] = min_time + ((double)Ds[i - 1][i] / (double)Ss[i - 1]);

      for (int j = 0; j < i - 1; j++) { // horse, not change horse
        if (Dss[i] - Dss[j] > Es[j]) {
          dp[i][j] = -1;
        } else {
          dp[i][j] = dp[i - 1][j] + ((double)Ds[i - 1][i] / (double)Ss[j]);
        }
      }
    }

    double ans = numeric_limits<double>::max();
    for (int i = 0; i < N - 1; i++) {
      if (dp[N - 1][i] >= 0) {
        ans = min(ans, dp[N - 1][i]);
      }
    }

    cout << "Case #" << t + 1 << ": " << setprecision(8) << ans << endl;
  }

  return 0;
}
