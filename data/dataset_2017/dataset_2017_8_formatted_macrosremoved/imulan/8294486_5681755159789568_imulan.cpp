#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const double INF = 1e12;

ll d[100][100];
double T[100][100];

void solve() {
  int n, q;
  cin >> n >> q;

  vector<int> e(n), s(n);
  for (int(i) = 0; (i) < (int)(n); ++(i))
    cin >> e[i] >> s[i];

  for (int(i) = 0; (i) < (int)(n); ++(i))
    for (int(j) = 0; (j) < (int)(n); ++(j)) {
      int tmp;
      cin >> tmp;
      if (tmp == -1)
        d[i][j] = LLONG_MAX / 4;
      else
        d[i][j] = tmp;
    }

  for (int(k) = 0; (k) < (int)(n); ++(k))
    for (int(i) = 0; (i) < (int)(n); ++(i))
      for (int(j) = 0; (j) < (int)(n); ++(j))
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

  // rep(i,n)rep(j,n) printf(" d[%d][%d] = %lld\n", i,j,d[i][j]);

  fill(T[0], T[100], INF);
  for (int(i) = 0; (i) < (int)(n); ++(i)) {
    // iをスタートにするので、iにいる馬を使う
    for (int(j) = 0; (j) < (int)(n); ++(j)) {
      if (i == j) {
        T[i][i] = 0;
        continue;
      }

      if (d[i][j] <= e[i])
        T[i][j] = (double)d[i][j] / s[i];
    }
  }

  for (int(k) = 0; (k) < (int)(n); ++(k))
    for (int(i) = 0; (i) < (int)(n); ++(i))
      for (int(j) = 0; (j) < (int)(n); ++(j))
        T[i][j] = min(T[i][j], T[i][k] + T[k][j]);

  for (int(QUERY) = 0; (QUERY) < (int)(q); ++(QUERY)) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;

    double ans = T[u][v];
    assert(ans < INF);
    printf(" %.10f", ans);
  }
  printf("\n");
}

int main() {
  int cases;
  cin >> cases;
  for (int(t) = 0; (t) < (int)(cases); ++(t)) {
    printf("Case #%d:", t + 1);
    solve();
  }
  return 0;
}
