#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ld INF = 1e11;

ld solve_small(const vector<int> &E, const vector<int> &S,
               const vector<vector<int>> &D) {
  int N = E.size();
  vector<ll> acm(N, 0);
  for (int i = 0; i < (int)(N - 1); i++)
    acm[i + 1] = acm[i] + D[i][i + 1];

  vector<vector<ld>> dp(N, vector<ld>(N + 1, INF));
  dp[0][N] = 0;
  for (int i = 0; i < (int)(N); i++)
    for (int j = 0; j < (int)(N + 1); j++) {
      if (dp[i][j] == INF)
        continue;
      for (int k = i + 1; k < N; ++k) {
        if (acm[k] - acm[i] > E[i])
          continue;
        dp[k][i] = min(dp[k][i], dp[i][j] + (ld)(acm[k] - acm[i]) / S[i]);
      }
    }

  ld res = INF;
  for (int j = 0; j < (int)(N); j++)
    res = min(res, dp[N - 1][j]);
  return res;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < (int)(T); t++) {
    int N, Q;
    cin >> N >> Q;
    vector<int> E(N), S(N);
    for (int i = 0; i < (int)(N); i++)
      cin >> E[i] >> S[i];
    vector<vector<int>> D(N, vector<int>(N));
    for (int i = 0; i < (int)(N); i++)
      for (int j = 0; j < (int)(N); j++)
        cin >> D[i][j];
    vector<int> U(Q), V(Q);
    for (int i = 0; i < (int)(Q); i++) {
      cin >> U[i] >> V[i];
      --U[i];
      --V[i];
    }

    cout << "Case #" << t + 1 << ":";
    for (int i = 0; i < (int)(Q); i++) {
      ld res = solve_small(E, S, D);
      cout << " " << fixed << setprecision(10) << res;
    }
    cout << endl;
  }
  return 0;
}
