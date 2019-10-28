#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const double INF = 1e15;
double D[100][100];

double E[100];
double S[100];

double dp[100];

typedef pair<double, int> P;
int U[100];
int V[100];

void solve() {
  int N, Q;
  cin >> N >> Q;

  for (int i = 0; i < N; i++) {
    cin >> E[i] >> S[i];
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> D[i][j];
      if (D[i][j] == -1)
        D[i][j] = INF;
    }
  }
  for (int i = 0; i < Q; i++) {
    cin >> U[i] >> V[i];
    U[i]--, V[i]--;
  }

  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
      }
    }
  }

  for (int i = 0; i < Q; i++) {
    fill((double *)begin(dp), (double *)end(dp), INF);
    priority_queue<P, vector<P>, greater<P>> q;
    dp[U[i]] = 0;
    q.push({0, U[i]});
    while (q.size()) {
      auto p = q.top();
      q.pop();
      double cost = p.first;
      int v = p.second;
      if (p.first > dp[v])
        continue;
      for (int u = 0; u < N; u++) {
        if (D[v][u] > E[v])
          continue;
        double ncost = cost + D[v][u] / S[v];
        if (dp[u] > ncost) {
          dp[u] = ncost;
          q.push({ncost, u});
        }
      }
    }
    cout << fixed << setprecision(15) << dp[V[i]];
    if (i == Q - 1)
      cout << endl;
    else
      cout << " ";
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cout << "Case #" << i + 1 << ": ";
    solve();
  }
}
