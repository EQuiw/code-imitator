#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define ALL(x) (x).begin(), (x).end()

typedef long long ll;
typedef long double ld;

const ld INF = 1e11;

ld solve_small(const vector<int>& E, const vector<int>& S, const vector<vector<int>>& D) {
  int N = E.size();
  vector<ll> acm(N, 0);
  REP(i,N - 1) acm[i + 1] = acm[i] + D[i][i + 1];

  vector<vector<ld>> dp(N, vector<ld> (N + 1, INF));
  dp[0][N] = 0;
  REP(i,N)REP(j,N + 1) {
    if(dp[i][j] == INF) continue;
    for(int k = i + 1; k < N; ++k) {
      if(acm[k] - acm[i] > E[i]) continue;
      dp[k][i] = min(dp[k][i], dp[i][j] + (ld)(acm[k] - acm[i]) / S[i]);
    }
  }

  ld res = INF;
  REP(j,N) res = min(res, dp[N - 1][j]);
  return res;
}

int main(){
  int T;
  cin >> T;
  REP(t,T) {
    int N, Q;
    cin >> N >> Q;
    vector<int> E(N), S(N);
    REP(i,N) cin >> E[i] >> S[i];
    vector<vector<int>> D(N, vector<int> (N));
    REP(i,N)REP(j,N) cin >> D[i][j];
    vector<int> U(Q), V(Q);
    REP(i,Q) {
      cin >> U[i] >> V[i];
      --U[i]; --V[i];
    }

    cout << "Case #" << t + 1 << ":";
    REP(i,Q) {
      ld res = solve_small(E, S, D);
      cout << " " << fixed << setprecision(10) << res;
    }
    cout << endl;
  }
  return 0;
}

