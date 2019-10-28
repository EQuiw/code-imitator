#include <bits/stdc++.h>

using namespace std;

int n, q;
vector<int> d, s;
int D[105][105];

double G[105][105];

void bfs(int u) {
  double dp[105];
  for (int i = 0; i < n; i++)
    dp[i] = 1e15;
  dp[u] = 0;
  queue<int> Q;
  Q.push(u);

  while (!Q.empty()) {
    int A = Q.front();
    Q.pop();
    if (dp[A] > d[u])
      continue;
    for (int i = 0; i < n; i++) {
      if (D[A][i] > 0 && (dp[i] > dp[A] + D[A][i])) {
        dp[i] = dp[A] + D[A][i];
        Q.push(i);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (dp[i] <= d[u])
      G[u][i] = 1.0 * dp[i] / s[u];
  }
}

int main() {
  int test;
  cin >> test;
  for (int cases = 1; cases <= test; cases++) {
    cin >> n >> q;
    d.clear();
    s.clear();
    for (int i = 0; i < n; i++) {
      int e, sp;
      cin >> e >> sp;
      d.push_back(e);
      s.push_back(sp);
    }

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        cin >> D[i][j];

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        if (i == j)
          G[i][j] = 0;
        else
          G[i][j] = 1e15;
      }

    for (int i = 0; i < n; i++) {
      bfs(i);
    }

    for (int k = 0; k < n; k++)
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
          if (G[i][k] + G[k][j] < G[i][j])
            G[i][j] = G[i][k] + G[k][j];
        }
    printf("Case #%d:", cases);
    while (q--) {
      int a, b;
      cin >> a >> b;
      a--;
      b--;
      printf(" %.8lf", G[a][b]);
    }
    cout << endl;
  }
  return 0;
}
