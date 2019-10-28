#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n, q, u, v;
long long e[102];
double s[102];
long long d[102][102];
double bt[102];
bool vi[102];

int main() {
  int tt;

  cin >> tt;

  for (int t = 1; t <= tt; ++t) {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
      cin >> e[i] >> s[i];
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        cin >> d[i][j];

    for (int k = 1; k <= n; ++k)
      for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
          if ((d[i][k] != -1) && (d[k][j] != -1) &&
              ((d[i][j] == -1) || (d[i][j] > d[i][k] + d[k][j])))
            d[i][j] = d[i][k] + d[k][j];

    cout << "Case #" << t << ":";

    for (int i = 0; i < q; ++i) {
      cin >> u >> v;
      for (int j = 1; j <= n; ++j) {
        bt[j] = -1;
        vi[j] = false;
      }
      bt[u] = 0;
      while (!vi[v]) {
        int cur = -1;
        for (int j = 1; j <= n; ++j)
          if (!vi[j] && (bt[j] != -1) && ((cur == -1) || (bt[cur] > bt[j])))
            cur = j;
        vi[cur] = true;
        for (int j = 1; j <= n; ++j)
          if ((d[cur][j] != -1) && (d[cur][j] <= e[cur]) &&
              ((bt[j] == -1) || ((bt[j] - bt[cur]) * s[cur] > d[cur][j])))
            bt[j] = bt[cur] + d[cur][j] / s[cur];
      }
      printf(" %.6lf", bt[v]);
    }
    cout << endl;
  }

  return 0;
}
