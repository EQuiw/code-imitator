#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
double h[MAXN][MAXN];
int d[MAXN][MAXN];
int e[MAXN];
int s[MAXN];
int N, Q;
double g[MAXN][MAXN];

void update(int st, int u, int r) {
  for (int i = 0; i < N; ++i) {
    if (u == i)
      continue;
    if (d[u][i] != -1 && d[u][i] <= r) {
      double est = double(d[u][i]) / s[st] + h[st][u];
      if (h[st][i] == -1 || h[st][i] > est) {
        h[st][i] = est;
        update(st, i, r - d[u][i]);
      }
    }
  }
}

void solve() {
  cin >> N >> Q;
  for (int i = 0; i < N; ++i) {
    cin >> e[i] >> s[i];
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> d[i][j];
      h[i][j] = -1;
    }
  }
  for (int i = 0; i < N; ++i) {
    h[i][i] = 0;
    update(i, i, e[i]);
  }
  memcpy(g, h, sizeof(h));
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      if (g[i][k] == -1)
        continue;
      for (int j = 0; j < N; ++j) {
        if (g[k][j] == -1)
          continue;
        if (g[i][j] == -1 || g[i][k] + g[k][j] < g[i][j]) {
          g[i][j] = g[i][k] + g[k][j];
        }
      }
    }
  }
  //  cout << endl;
  //  for (int i = 0; i < N; ++i) {
  //    for (int j = 0; j < N; ++j) {
  //      cout << h[i][j] << ' ';
  //    }
  //    cout << endl;
  //  }
  //  cout << endl;
  //
  //  cout << endl;
  //  for (int i = 0; i < N; ++i) {
  //    for (int j = 0; j < N; ++j) {
  //      cout << g[i][j] << ' ';
  //    }
  //    cout << endl;
  //  }
  //  cout << endl;

  for (int i = 0; i < Q; ++i) {
    int u, v;
    cin >> u >> v;
    printf("%.8f", g[u - 1][v - 1]);
    if (i != Q - 1) {
      cout << ' ';
    }
  }
  cout << endl;
}

int main() {
  int T;
  cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    printf("Case #%d: ", cas);
    solve();
  }
}
