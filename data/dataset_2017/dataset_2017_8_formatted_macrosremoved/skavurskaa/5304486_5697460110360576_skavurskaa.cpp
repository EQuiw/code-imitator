#include <bits/stdc++.h>
using namespace std;

int dp[1 << 18];
int N, P;
double ing[2], pack[10][10];

int solve(int mask) {
  if (dp[mask] == -1) {
    dp[mask] = 0;
    for (int i = 0; i < P; i++)
      for (int k = 0; k < P; k++)
        if (!(mask & (1 << i)) && !(mask & (1 << (P + k)))) {
          double A = pack[0][i] / (1.1 * ing[0]);
          double B = pack[0][i] / (0.9 * ing[0]);
          double C = pack[1][k] / (1.1 * ing[1]);
          double D = pack[1][k] / (0.9 * ing[1]);
          pair<double, double> rng = {max(A, C), min(B, D)};
          if ((int)ceil(rng.first) <= (int)floor(rng.second)) {
            int mk = mask;
            mk |= 1 << i;
            mk |= 1 << (P + k);
            dp[mask] = max(dp[mask], solve(mk) + 1);
          }
        }
  }
  return dp[mask];
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cin >> N >> P;

    for (int i = 0; i < N; i++)
      cin >> ing[i];
    for (int i = 0; i < N; i++)
      for (int j = 0; j < P; j++)
        cin >> pack[i][j];

    int ans = 0;
    if (N == 1) {
      for (int i = 0; i < P; i++)
        for (int j = 1; j <= 1000000; j++)
          if (0.9 * j * ing[0] <= pack[0][i] &&
              pack[0][i] <= 1.1 * j * ing[0]) {
            ans++;
            break;
          }
    } else {
      memset(dp, -1, sizeof(dp));
      ans = solve(0);
    }
    cout << "Case #" << t << ": " << ans << endl;
  }
}
